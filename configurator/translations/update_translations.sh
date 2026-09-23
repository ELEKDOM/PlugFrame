#!/bin/bash
set -e

cd "$(dirname "$0")"

find ../ \( -name "*.cpp" -o -name "*.h" -o -name "*.ui" \) > sources.lst

lupdate @sources.lst -ts configurator_fr.ts
linguist configurator_fr.ts
lrelease configurator_fr.ts -qm configurator_fr.qm

