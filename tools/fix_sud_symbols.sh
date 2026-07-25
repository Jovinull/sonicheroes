#!/usr/bin/env bash
set -euo pipefail

object=$1
stamp=$2
temporary="${object}.symbols.tmp"

llvm-objcopy \
	--globalize-symbol=@52 \
	--globalize-symbol=@55 \
	--redefine-sym @52=lbl_17_rodata_3C8 \
	--redefine-sym @55=lbl_17_rodata_3D8 \
	--redefine-sym sud_marker=lbl_17_rodata_3E4 \
	--redefine-sym sud_tail=lbl_17_rodata_3E8 \
	"$object" "$temporary"
touch -r "$object" "$temporary"
mv "$temporary" "$object"
touch "$stamp"
