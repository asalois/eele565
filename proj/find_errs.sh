#!/bin/bash
grep -B3 -A1 -P 'xored = (?!0)' out.txt
