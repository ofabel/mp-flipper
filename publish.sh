#!/usr/bin/env bash

readonly BRANCH="${1}"
readonly TARGET='./temp'
readonly REMOTE='git@github.com:ofabel/mp-flipper.git'

set -e

rm -rf ${TARGET}

git clone --branch ${BRANCH} --single-branch ${REMOTE} ${TARGET} || (git init -b ${BRANCH} ${TARGET} && cd ${TARGET} && git remote add origin ${REMOTE} && cd ..)

rm -rf ${TARGET}/*

cp *.c *.h ${TARGET}
cp -r ./extmod ./genhdr ./py ./shared ${TARGET}

cd ${TARGET}

git add . && git commit -m "library update" && git push origin ${BRANCH} || cd .

cd ..

rm -rf ${TARGET}

exit 0
