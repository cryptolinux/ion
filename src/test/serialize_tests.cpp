// Copyright (c) 2012-2013 The Bitcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "serialize.h"
#include "streams.h"
#include "hash.h"
#include "test/test_ion.h"

#include <stdint.h>

#include <boost/test/unit_test.hpp>


BOOST_FIXTURE_TEST_SUITE(serialize_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(varints)
{
    // encode

    CDataStream ss(SER_DISK, 0);
    CDataStream::size_type size = 0;
    for (int i = 0; i < 100000; i++) {
        ss << VARINT(i);
        size += ::GetSerializeSize(VARINT(i), 0, 0);
        BOOST_CHECK(size == ss.size());
    }

    for (uint64_t i = 0;  i < 100000000000ULL; i += 999999937) {
        ss << VARINT(i);
        size += ::GetSerializeSize(VARINT(i), 0, 0);
        BOOST_CHECK(size == ss.size());
    }

    // decode
    for (int i = 0; i < 100000; i++) {
        int j = -1;
        ss >> VARINT(j);
        BOOST_CHECK_MESSAGE(i == j, "decoded:" << j << " expected:" << i);
    }

    for (uint64_t i = 0;  i < 100000000000ULL; i += 999999937) {
        uint64_t j = -1;
        ss >> VARINT(j);
        BOOST_CHECK_MESSAGE(i == j, "decoded:" << j << " expected:" << i);
    }
}

BOOST_AUTO_TEST_CASE(varints_bitpatterns)
{
    CDataStream ss(SER_DISK, 0);
    ss << VARINT(0); BOOST_CHECK_EQUAL(HexStr(ss), "00"); ss.clear();
    ss << VARINT(0x7f); BOOST_CHECK_EQUAL(HexStr(ss), "7f"); ss.clear();
    ss << VARINT((int8_t)0x7f); BOOST_CHECK_EQUAL(HexStr(ss), "7f"); ss.clear();
    ss << VARINT(0x80); BOOST_CHECK_EQUAL(HexStr(ss), "8000"); ss.clear();
    ss << VARINT((uint8_t)0x80); BOOST_CHECK_EQUAL(HexStr(ss), "8000"); ss.clear();
    ss << VARINT(0x1234); BOOST_CHECK_EQUAL(HexStr(ss), "a334"); ss.clear();
    ss << VARINT((int16_t)0x1234); BOOST_CHECK_EQUAL(HexStr(ss), "a334"); ss.clear();
    ss << VARINT(0xffff); BOOST_CHECK_EQUAL(HexStr(ss), "82fe7f"); ss.clear();
    ss << VARINT((uint16_t)0xffff); BOOST_CHECK_EQUAL(HexStr(ss), "82fe7f"); ss.clear();
    ss << VARINT(0x123456); BOOST_CHECK_EQUAL(HexStr(ss), "c7e756"); ss.clear();
    ss << VARINT((int32_t)0x123456); BOOST_CHECK_EQUAL(HexStr(ss), "c7e756"); ss.clear();
    ss << VARINT(0x80123456U); BOOST_CHECK_EQUAL(HexStr(ss), "86ffc7e756"); ss.clear();
    ss << VARINT((uint32_t)0x80123456U); BOOST_CHECK_EQUAL(HexStr(ss), "86ffc7e756"); ss.clear();
    ss << VARINT(0xffffffff); BOOST_CHECK_EQUAL(HexStr(ss), "8efefefe7f"); ss.clear();
    ss << VARINT(0x7fffffffffffffffLL); BOOST_CHECK_EQUAL(HexStr(ss), "fefefefefefefefe7f"); ss.clear();
    ss << VARINT(0xffffffffffffffffULL); BOOST_CHECK_EQUAL(HexStr(ss), "80fefefefefefefefe7f"); ss.clear();
}

BOOST_AUTO_TEST_CASE(compactsize)
{
    CDataStream ss(SER_DISK, 0);
    std::vector<char>::size_type i, j;

    for (i = 1; i <= MAX_SIZE; i *= 2)
    {
        WriteCompactSize(ss, i-1);
        WriteCompactSize(ss, i);
    }
    for (i = 1; i <= MAX_SIZE; i *= 2)
    {
        j = ReadCompactSize(ss);
        BOOST_CHECK_MESSAGE((i-1) == j, "decoded:" << j << " expected:" << (i-1));
        j = ReadCompactSize(ss);
        BOOST_CHECK_MESSAGE(i == j, "decoded:" << j << " expected:" << i);
    }
}

static bool isCanonicalException(const std::ios_base::failure& ex)
{
    std::ios_base::failure expectedException("non-canonical ReadCompactSize()");

    // The string returned by what() can be different for different platforms.
    // Instead of directly comparing the ex.what() with an expected string,
    // create an instance of exception to see if ex.what() matches
    // the expected explanatory string returned by the exception instance.
    return strcmp(expectedException.what(), ex.what()) == 0;
}


BOOST_AUTO_TEST_CASE(noncanonical)
{
    // Write some non-canonical CompactSize encodings, and
    // make sure an exception is thrown when read back.
    CDataStream ss(SER_DISK, 0);
    std::vector<char>::size_type n;

    // zero encoded with three bytes:
    ss.write("\xfd\x00\x00", 3);
    BOOST_CHECK_EXCEPTION(ReadCompactSize(ss), std::ios_base::failure, isCanonicalException);

    // 0xfc encoded with three bytes:
    ss.write("\xfd\xfc\x00", 3);
    BOOST_CHECK_EXCEPTION(ReadCompactSize(ss), std::ios_base::failure, isCanonicalException);

    // 0xfd encoded with three bytes is OK:
    ss.write("\xfd\xfd\x00", 3);
    n = ReadCompactSize(ss);
    BOOST_CHECK(n == 0xfd);

    // zero encoded with five bytes:
    ss.write("\xfe\x00\x00\x00\x00", 5);
    BOOST_CHECK_EXCEPTION(ReadCompactSize(ss), std::ios_base::failure, isCanonicalException);

    // 0xffff encoded with five bytes:
    ss.write("\xfe\xff\xff\x00\x00", 5);
    BOOST_CHECK_EXCEPTION(ReadCompactSize(ss), std::ios_base::failure, isCanonicalException);

    // zero encoded with nine bytes:
    ss.write("\xff\x00\x00\x00\x00\x00\x00\x00\x00", 9);
    BOOST_CHECK_EXCEPTION(ReadCompactSize(ss), std::ios_base::failure, isCanonicalException);

    // 0x01ffffff encoded with nine bytes:
    ss.write("\xff\xff\xff\xff\x01\x00\x00\x00\x00", 9);
    BOOST_CHECK_EXCEPTION(ReadCompactSize(ss), std::ios_base::failure, isCanonicalException);
}

BOOST_AUTO_TEST_CASE(insert_delete)
{
    // Test inserting/deleting bytes.
    CDataStream ss(SER_DISK, 0);
    BOOST_CHECK_EQUAL(ss.size(), 0);

    ss.write("\x00\x01\x02\xff", 4);
    BOOST_CHECK_EQUAL(ss.size(), 4);

    char c = (char)11;

    // Inserting at beginning/end/middle:
    ss.insert(ss.begin(), c);
    BOOST_CHECK_EQUAL(ss.size(), 5);
    BOOST_CHECK_EQUAL(ss[0], c);
    BOOST_CHECK_EQUAL(ss[1], 0);

    ss.insert(ss.end(), c);
    BOOST_CHECK_EQUAL(ss.size(), 6);
    BOOST_CHECK_EQUAL(ss[4], (char)0xff);
    BOOST_CHECK_EQUAL(ss[5], c);

    ss.insert(ss.begin()+2, c);
    BOOST_CHECK_EQUAL(ss.size(), 7);
    BOOST_CHECK_EQUAL(ss[2], c);

    // Delete at beginning/end/middle
    ss.erase(ss.begin());
    BOOST_CHECK_EQUAL(ss.size(), 6);
    BOOST_CHECK_EQUAL(ss[0], 0);

    ss.erase(ss.begin()+ss.size()-1);
    BOOST_CHECK_EQUAL(ss.size(), 5);
    BOOST_CHECK_EQUAL(ss[4], (char)0xff);

    ss.erase(ss.begin()+1);
    BOOST_CHECK_EQUAL(ss.size(), 4);
    BOOST_CHECK_EQUAL(ss[0], 0);
    BOOST_CHECK_EQUAL(ss[1], 1);
    BOOST_CHECK_EQUAL(ss[2], 2);
    BOOST_CHECK_EQUAL(ss[3], (char)0xff);

    // Make sure GetAndClear does the right thing:
    CSerializeData d;
    ss.GetAndClear(d);
    BOOST_CHECK_EQUAL(ss.size(), 0);
}

// Change struct size and check if it can be deserialized
// from old version archive and vice versa
struct old_version
{
    int field1;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(field1);
    }
};\
struct new_version
{
    int field1;
    int field2;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(field1);
        if(ser_action.ForRead() && (s.size() == 0))
        {
            field2 = 0;
            return;
        }
        READWRITE(field2);
    }
};

BOOST_AUTO_TEST_CASE(check_backward_compatibility)
{
    CDataStream ss(SER_DISK, 0);
    old_version old_src({5});
    ss << old_src;
    new_version new_dest({6, 7});
    BOOST_REQUIRE_NO_THROW(ss >> new_dest);
    BOOST_REQUIRE(old_src.field1 == new_dest.field1);
    BOOST_REQUIRE(ss.size() == 0);

    new_version new_src({6, 7});
    ss << new_src;
    old_version old_dest({5});
    BOOST_REQUIRE_NO_THROW(ss >> old_dest);
    BOOST_REQUIRE(new_src.field1 == old_dest.field1);
}

BOOST_AUTO_TEST_CASE(class_methods)
{
    int intval(100);
    bool boolval(true);
    std::string stringval("testing");
    const char* charstrval("testing charstr");
    CMutableTransaction txval;
    CSerializeMethodsTestSingle methodtest1(intval, boolval, stringval, charstrval, txval);
    CSerializeMethodsTestMany methodtest2(intval, boolval, stringval, charstrval, txval);
    CSerializeMethodsTestSingle methodtest3;
    CSerializeMethodsTestMany methodtest4;
    CDataStream ss(SER_DISK, PROTOCOL_VERSION);
    BOOST_CHECK(methodtest1 == methodtest2);
    ss << methodtest1;
    ss >> methodtest4;
    ss << methodtest2;
    ss >> methodtest3;
    BOOST_CHECK(methodtest1 == methodtest2);
    BOOST_CHECK(methodtest2 == methodtest3);
    BOOST_CHECK(methodtest3 == methodtest4);

    CDataStream ss2(SER_DISK, PROTOCOL_VERSION, intval, boolval, stringval, FLATDATA(charstrval), txval);
    ss2 >> methodtest3;
    BOOST_CHECK(methodtest3 == methodtest4);
}

BOOST_AUTO_TEST_SUITE_END()
