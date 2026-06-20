#!/bin/bash
set -e

cd "$(dirname "$0")"

find ../ \( -name "*.cpp" -o -name "*.h" -o -name "*.ui" \) > sources.lst

lupdate @sources.lst -ts plugframe_fr.ts
linguist plugframe_fr.ts
lrelease plugframe_fr.ts -qm plugframe_fr.qm

