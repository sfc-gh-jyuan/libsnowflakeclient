#!/bin/bash -e
#
# Build ARROW library
#
function usage() {
    echo "Usage: `basename $0` [-t <Release|Debug>]"
    echo "Build ARROW library"
    echo "-t <Release/Debug> : Release or Debug builds"
    echo "-v                 : Version"
    exit 2
}
set -o pipefail

#Change the version in the arrow.mk to build 
ARROW_VERSION=0.15.0

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
source $DIR/_init.sh $@
source $DIR/utils.sh

[[ -n "$GET_VERSION" ]] && echo $ARROW_VERSION && exit 0

THIS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Download from S3 bucket for now due to issue with AWS credentials.
if [[ "$PLATFORM" == "linux" ]]; then
    # chmod +wx $DEPS_DIR
    # cp $THIS_DIR/arrow.mk $DEPS_DIR
    # cd $DEPS_DIR
    # BUILD_TYPE=$BUILD_TYPE CC=gcc52 CXX=g++52 make -f arrow.mk
    echo "[INFO] For ${PLATFORM}, use pre-built binaries for Arrow"
    local zip_file_name=$(get_zip_file_name arrow $ARROW_VERSION $target)
    download_from_sfc_dev1_data arrow $ARROW_VERSION $target
    tar xzf $DEPENDENCY_DIR/$zip_file_name
    rm $DEPENDENCY_DIR/$zip_file_name
elif [[ "$PLATFORM" == "darwin" ]]; then
    echo "[INFO] For ${PLATFORM}, use pre-built binaries for Arrow"
    local zip_file_name=$(get_zip_file_name arrow $ARROW_VERSION $target)
    download_from_sfc_dev1_data arrow $ARROW_VERSION $target
    tar xzf $DEPENDENCY_DIR/$zip_file_name
    rm $DEPENDENCY_DIR/$zip_file_name
else
    echo "[ERROR] $PLATFORM is not supported"
fi
