# Seeds

Utility to generate the seeds.txt list that is compiled into the client
(see [src/chainparamsseeds.h](/src/chainparamsseeds.h) and other utilities in [contrib/seeds](/contrib/seeds)).

Be sure to update `PATTERN_AGENT` in `makeseeds.sh` to include the current version,
and remove old versions as necessary.

The seeds compiled into the release are created from chainz (cryptoid)' DNS seed data, like this:

    chmod +x ./contrib/seedds/makeseeds.sh && ./contrib/seedds/makeseeds.sh

Make sure to use a recent block height in the "protx list" call. After updating, create a PR and
specify which block height you used so that reviewers can re-run the same commands and verify
that the list is as expected.

## Dependencies

Ubuntu:

    sudo apt-get install python3-dnspython
