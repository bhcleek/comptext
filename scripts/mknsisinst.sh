#!/bin/sh

### Script to create a win32 installer file
### 20090510  Stelios Bounanos M0GLD, Dave Freese W1HKJ

### change for the target application
comptext_name=comptext
comptext_bin=comptext.exe

if [ $# -ne 2 ]; then
    echo "Syntax: $0 data-dir build-dir" >&2
    exit 1
fi

if [ -z "$PACKAGE_TARNAME" ]; then
    echo "E: \$PACKAGE_TARNAME undefined"
    exit 1
fi

PWD=`pwd`
data="${PWD}/$1"
build="${PWD}/$2"

# more sanity checks
for d in "$data" "$build"; do
    test -d "$d" && continue
    echo "E: ${d}: not a directory" >&2
    exit 1
done
if ! test -w "$build"; then
    echo "E: ${build} is not writeable" >&2
    exit 1
fi

set -e

test "x$NOSTRIP" = "x" && $STRIP -S "$comptext_bin"
def="$def -Dcomptext_NAME=$comptext_name -Dcomptext_BINARY=$comptext_bin -Dcomptext_VERSION=$PACKAGE_VERSION"

$MAKENSIS -V2 -NOCD -D"INSTALLER_FILE=$INSTALLER_FILE" -D"LICENSE_FILE=$data/../COPYING" \
    -D"SUPPORT_URL=$PACKAGE_HOME" -D"UPDATES_URL=$PACKAGE_DL" $def "$data/win32/fl_app.nsi"
