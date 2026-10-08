# storyTable.cpp complete-unit evidence

Symbolic metadata explicitly names `storyTable.cpp` and `C_PLUS_PLUS`, with
STORYMANAGE (eight bytes: currentStory and seqStep), STORY_TABLE (seqFlag,
SEQ_TYPE, data), STORY_INFO (table pointer and element count), five private
sequence tables, bonus-stage mappings, the must-exit list, static storyInfo,
and the StoryManage singleton. No PS2 instruction bytes were used.

The retail GameCube unit is larger than the earlier symbolic version:

| Body | Address | Size |
| --- | --- | --- |
| Progress persistence helper, original name unknown | 0x801380B8 | 824 |
| Current-story getter, original name unknown | 0x801383F0 | 36 |
| MustExit | 0x80138414 | 84 |
| SetBonusStage | 0x80138468 | 136 |
| WarpSeqStep | 0x801384F0 | 372 |
| CurrentMovieNumber | 0x80138664 | 96 |
| CheckCurrentSeqType | 0x801386C4 | 64 |
| Staff-roll step, original name unknown | 0x80138704 | 196 |
| StepMovieSeq | 0x801387C8 | 252 |
| StepStageSeq | 0x801388C4 | 208 |
| CheckStoryProgress | 0x80138994 | 264 |
| Restart helper, original name unknown | 0x80138A9C | 476 |
| SetStory | 0x80138C78 | 596 |

Four GameCube additions retain address-based C boundary names; their original
names are not asserted. StepMovieSeq obtains the current movie internally in
this build, and CheckStoryProgress has an additional signed count argument.
These differences follow the GameCube calling convention and accesses, not
blind transplantation of the PS2 signatures. The metadata-named getCurrentSeq
and SetActionStageConnect helpers survive as inline code.

The complete text is `0x801380B8–0x80138ECC` (3604 bytes). The preceding two
functions are the separately identified enemy utility timer unit; the next
unit is the already reconstructed movie.cpp. The leading progress helper
reads private storyInfo and updates four saved-data progress bytes. The getter
accesses the same eight-byte singleton layout. These operations, the private
table references throughout the cluster, and the matching neighboring source
identities establish ownership beyond the old eight-body partial split.

Owned sections are extab `0x8000B8F0–0x8000B940` (80 bytes), extabindex
`0x80011950–0x800119C8` (120), data `0x8028C448–0x8028CA70` (1576), and sbss
`0x8042C7E0–0x8042C7E8` (8). The data contains five STORY_TABLE arrays with
27/27/28/27/8 records, three signed stage enums in mustExitBeforePlay, fifteen
BONUSSTAGE_TBL pairs, and five STORY_INFO records. Retail table values and
counts are authoritative; the earlier metadata has differing counts.

This replaces the provisional `voice_sequence.cpp` fragment, which covered
only the last eight bodies and the final portion of the data. The complete
C++ source retains its behavior while removing every per-function language
and optimization pragma. External consumers receive only same-address symbol
renames. SDK, Action, saved-data and movie globals remain externally owned.

## Whole-unit compilation and inline evidence

STORYMANAGE's helper calls account for repeated code in the retail functions:
getCurrentSeq scans sequence flags, SetActionStageConnect builds the Action
stage list, and the progress persistence helper expands four calls to
CheckStoryProgress. The normal source early-return clamp preserves both the
standalone CheckStoryProgress body and its four expanded control-flow paths.
The source has no injected instructions, artificial branches or normalizer.

The retained whole-unit mode is `-bool off -inline auto,deferred` with the
ordinary project optimization/exception settings. All definitions participate
in the same mode. Three raw compiler comparisons provide the emission evidence:

- Retained source with auto,deferred: 3604 text bytes, all thirteen bodies and
  their retail order exact.
- Same source with auto: 3616 text bytes; an extra getCurrentSeq body is emitted
  and SetStory shrinks from 596 to 532 bytes.
- Retail-order definitions with auto: 3272 text bytes; the leading progress
  helper is 164 bytes instead of 824 because the later method does not expand.

The retained definition order permits the compiler's deferred expansion and
emission to reproduce the complete unit. Metadata and GameCube call structure
support the helper boundaries; the original source line order and historical
compiler flags are unknown. The evidence is for a reviewed whole-unit
reconstruction setting, not a claim that original source formatting was recovered.

Single-object verification passes all thirteen body bytes and bindings, every
allocated section's bytes/size/alignment/flags, and all 200 effective
relocations. Independent whole-object, metadata/control-flow and six-consumer
reviews pass. All-source compilation of the supported G9SE8P main DOL and all
seventeen RELs passes with the reconstructed source linked; all eighteen
reference hashes pass. Progress/report generation, 62 automated tests and both
policies pass. Compilation and binary comparison do not establish runtime or
physical-hardware validation.
