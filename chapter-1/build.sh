#!/usr/bin/env bash

EXERCISES=./exercises/*/*.c
echo "[-] Build exercises..."
for f in $EXERCISES
do
    echo "[-] Build $f"
    cc "$f" -o "$f.out"
done
echo "[+] Done."

FOLLOW_ALONGS=./follow-alongs/*.c
echo "[-] Build follow-alongs..."
for f in $FOLLOW_ALONGS
do
    echo "[-] Build $f"
    cc "$f" -o "$f.out"
done
echo "[+] Done."
