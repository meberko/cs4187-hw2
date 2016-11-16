#! /bin/bash

encdec "te st" "te st2" "te'st" "te.s\"t+=32\\"
echo illegals | encdec
diff -s /bin/cp /tmp/dir/mycp
