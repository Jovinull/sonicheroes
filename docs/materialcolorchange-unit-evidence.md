# Material color change plugin translation unit

The complete GameCube unit occupies `.text` `0x8005F490..0x8005FA0C`
(1,404 bytes, sixteen functions). Its positive ownership anchor is
`RpAtomicMCCPluginAttach`: it registers plugin ID `0x1FF`, a 32-byte payload,
and the constructor, destructor, copier, read, write, and size callbacks that
account for every local callback in the symbolic method inventory. The nine
public accessors preceding registration match the metadata names, field
offsets, argument types, and behavior.

The PS2 DWARF producer identifies `src/plugin/materialcolorchange.c` as
`language=C_PLUS_PLUS`. The reconstruction therefore uses a `.cpp` source.
Public `RpAtomicMCC*` functions have unmangled metadata names; local callbacks
have C++ manglings. PS2 evidence used here is symbolic metadata only; executable
behavior and instruction matching come exclusively from GameCube code.

| GameCube address | Function |
| --- | --- |
| `8005F490` | `RpAtomicMCCGetCustomRenderCallBack` |
| `8005F4B4` | `RpAtomicMCCSetCustomRenderCallBack` |
| `8005F4E8` | `RpAtomicMCCGetUsrData` |
| `8005F50C` | `RpAtomicMCCSetUsrData` |
| `8005F64C` | `RpAtomicMCCSetActive` |
| `8005F670` | `RpAtomicMCCSetMaterialPointer` |
| `8005F694` | `RpAtomicMCCSetColor` |
| `8005F6D4` | `RpAtomicMCCGetMaterialPointer` |
| `8005F6F4` | `RpAtomicMCCGetColor` |
| `8005F710` | `RpAtomicMCCPluginAttach` |
| `8005F794` | `MCCDataGetStreamSize` |
| `8005F79C` | `MCCDataWriteStream` |
| `8005F844` | `MCCDataReadStream` |
| `8005F904` | `MCCDataCopier` |
| `8005F984` | `MCCDataDestructor` |
| `8005F988` | `MCCDataConstructor` |

`MCCLocal` has RGBA bytes at offset 0, a material pointer at 4, signed active
flag at 8, three signed user words at 12, and `OBJ_CUSTOMRENDER` at 24. The
last structure contains a data pointer and an atomic-render callback. These
metadata layouts agree with every GameCube access and the registered size.
The unit owns `LocalOffset`, initialized to -1, at `.sdata`
`0x8042B238..0x8042B23C`, followed by four alignment bytes. Its constructor's
zero RGBA initializer occupies `.sbss2` `0x804302A8..0x804302AC`, also followed
by four alignment bytes. Exception records are `0x800069E4..0x80006A04` and
indices `0x8000D438..0x8000D468`.

The source preserves the retail accessors' positive-offset test, caller-sized
user-data copy, partial constructor/copy initialization, and stream conversion
behavior. In particular, writing the 32-byte payload initializes the first
24 bytes before passing it to the endian conversion and stream write routines;
it does not initialize the custom-render fields. This is retail behavior,
not an inferred serialization repair. Reading restores only color, material,
and active through the public accessors.

The complete unit uses ordinary C++, `-inline auto`, and the whole-unit
options `-bool off`, `-Cpp_exceptions on`, and
`-opt noschedule,nopeephole`. Boolean comparison lowering, exception records,
and operation order match the retail output under these settings. No object
post-processor, assembly, artificial padding, or per-function flags are added.
Canonical symbols replace raw address names in existing callers, including
shared `.inc` files. Existing provisional caller layouts are not reconstructed
as part of this unit. The old standalone stream-size leaf is subsumed.

All sixteen bodies and normalized relocations match, including all direct
call targets. Whole text, exception records, and initialized data also match.
The native Matching source produces a byte-identical main DOL. The complete
supported G9SE8P matrix compiles and passes all eighteen reference hashes
(main DOL and seventeen RELs). All 62 automated tests and language/object
post-processor policy checks pass. Compilation and binary comparison do not
claim runtime or physical-hardware validation.
