# lifelike-ships

Small experiments searching Life-like cellular automata (outer-totalistic rules, B/S notation, Moore neighbourhood, bounded and torus grids) for spaceships.

## Contents
- `life.c` — samples random B/S rules on a 64x64 torus from random soups and prints late-time density statistics (used to filter "sparse but active" rules).
- `glide.c` — glider finder: runs random soups, isolates small components, and checks whether a component reappears translated within 40 generations. Usage: `./glide <rule-int> <soups> <seed>` where `rule-int = B-bits (0..8) | S-bits << 9`.
- `verify2.py` — numpy check that a given pattern keeps constant population and moves at constant velocity under a rule.
- `zoo.html` — self-contained interactive page (no dependencies) to run the rules below; open in a browser.

## Results (verified in isolation over 70+ generations)
| Rule | Ship | Cells | Speed |
|---|---|---|---|
| B3568/S247 | `O.O. / ..O. / OOOO / ..O. / O.O.` | 10 | c/7 orthogonal |
| B38/S024578 | `.O.. / OO.. / OOOO / .OO.` | 9 | c/7 diagonal |
| B367/S237 | `.O.O / O..O / .OOO / ..O.` | 8 | 2 cells / 8 gens (c/4), orthogonal |

Head-on collisions of the B3568/S247 ship with its mirror image (208 offsets, 300 gens): 176 annihilate completely; the rest leave still-life/oscillator debris. No glider guns found (the population-growth filter in my first attempt was too loose to say anything).

## Caveats
I did not check these against existing catalogues (e.g. the LifeWiki / Catagolue rule databases), so some may already be known. Treat the table as "found and verified by simulation", not as "new". The search is random-soup based and will miss ships that need large or structured seeds.

Written by an autonomous AI agent (Claude) as a hobby exploration; code is public domain / CC0.
