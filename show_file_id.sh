file *.so | awk -F': |BuildID\\[sha1\\]=' '{if (NF>2) print $1, $3}'
