# Native LSC reconstruction audit

This is one completed correction covering all 26 surviving functions in the
contiguous GameCube LSC family. Four reconstructed source groups replace the
previous error fragment and oversized API slice. Their boundaries and filenames
are inferred, not established by surviving source-file markers.

## Ownership evidence

All ranges below are half-open.

| Source | Functions | Text | Read-only data | BSS |
| --- | ---: | --- | --- | --- |
| `lsc_err.c` | 4 | `8021F410–8021F544` | none | `80420770–80420878` |
| `lsc.c` | 19 | `8021F544–802201E0` | `8023FDF8–8023FEFD` | `80420878–80420884` |
| `lsc_ini.c` | 2 | `802201E0–802202FC` | `8023FF00–8023FF34` | `80420888–80422C0C` |
| `lsc_svr.c` | 1 | `802202FC–80220544` | `8023FF38–8023FF4D` | none |

The error group owns its callback, callback object and 256-byte message buffer.
The public API owns three status-callback words and seven error strings.
Initialization/shutdown own the banner, its single pointer, initialization count
and sixteen 0x238-byte objects. The executor and its three state handlers use
the supplied object and external APIs, not the lifecycle globals; their sole
error string begins at the next independently aligned read-only address.

Minimal local PS2 symbols corroborate the separate status words, error words
and buffer, four-byte build pointer, four-byte initialization count, and
9,088-byte object pool. Function ordering separates the public API, error/critical
section adapters, lifecycle operations, and state handlers/executor. No matching
source-file marker was found. The PS2 `lsc_obj_mark` is the separate string
`MARK:lsc_obj`, not evidence for the old unused GameCube status-padding integer.

The rejected merged-26-function interpretation grouped related APIs too broadly:
it combined independently addressed BSS pools and encouraged unwanted public
API inlining. The four-group interpretation instead explains the call graph,
storage ownership and natural eight-byte inter-unit alignment together. A string
gap alone was not treated as proof of a source boundary. GCCI has its own error
state; its neighboring object and SJCRS are unchanged.

## Native source and contract decisions

- All four sources use ordinary C with the existing common compiler settings,
  including `-inline auto`. There is no new language/compiler-mode exception.
  The CRI C boundary remains reviewed; historical file language is unresolved.
- All old per-function optimization/inlining pragmas, dummy comma expression,
  manually expanded Stop/Reset bodies, synthetic status/pool padding and extra
  null banner-pointer element are removed. No instruction postprocessor is used.
- A signed-long constructor loop index naturally preserves the target guard
  while initializing all sixteen records. The previous hand-unrolled conditional
  and propagation override are unnecessary.
- The ring-entry helper returns the current slot and writes the previous index;
  both outputs are consumed. The checksum loop loads each word into a used local
  before accumulation. Direct compound-load spelling instead lets the compiler
  inline the entire range-entry function into its filename wrapper. These are
  meaningful source expressions, but their historical spellings are unproven.
- A checked start-stream helper explains the retained state check after the
  caller resets `streamStarted`. Its condition governs actual start operations;
  there is no empty condition or unused state.
- LSC uses the existing `CriStream` contract. The native caller stores the
  SJRBF creator's result at object offset 0x10 and passes that same pointer to
  LSC_Create. The shared vtable's count operation is at offset 0x24.
- The requested length is a signed sector count, not a pointer: STM shifts the
  file-range count left by eleven to obtain bytes, and its count setter accepts
  sectors or derives a rounded count from bytes. Offset 0x2C in LSC therefore
  stores `requestedSectors`. The STM flow-limit setter returns an integer
  success value. Unaccessed structure bytes remain explicitly unknown.
- Initialization performs an otherwise unused version-anchor load. Removing
  the volatile pointer qualifier removes the native address/load pair and
  shrinks the function from 120 to 112 bytes. The qualifier reconstructs an
  observable read; it is not claimed as proof of the historical declaration.
- Shared MSL declarations agree with this repository's existing `strlen` and
  `vsprintf` definitions and the established `__va_list` representation.

## Verification

All 26 functions match natively. The four complete allocated-section inventories
agree in bytes, sizes, types, flags and alignment against the reconstructed target
objects: 4,404 text bytes, 334 read-only bytes and 9,368 BSS bytes. All 44
meaningful function/object symbols and 150 resolved relocations agree, as do the
undefined-import inventories. Defined zero-size function/object entries are also
audited; there is no extra helper or import. Target-object ELF metadata is not
independent proof of historical object metadata.

The verifier excludes only generated hidden alignment-gap labels after checking
that their bytes are zero and no relocation points into them. Their bytes remain
part of the complete section comparison. Normal file/section/pool-base labels
are not treated as additional functions or data objects.

The source-linked G9SE8P release, all-source build, progress/report generation,
54 automated tests, language policy, 52 existing postprocessor policy checks,
and all eighteen DOL/REL hashes pass. The linker input selects all four native
LSC source objects. Complete SJMEM, SJRBF, SJUNI and SJ object audits pass;
neighboring GCCI/SJCRS split objects compare identically to the preceding base.
G9SE8P is the only configured supported release target. These results do not
constitute runtime or physical-hardware validation.
