#!/usr/bin/env bash

readonly BRANCH='lib-release'
readonly TARGET='./temp'

set -e

rm -rf ${TARGET}

git clone --branch ${BRANCH} git@github.com:ofabel/mp-flipper.git ${TARGET}

rm -rf ${TARGET}/*

cp *.c *.h temp/
cp -r ./extmod ./genhdr ./py ./shared ${TARGET}

cd ${TARGET}

git add . && git commit -m "library update" && git push origin ${BRANCH} || cd .

cd ..

rm -rf ${TARGET}

exit 0
