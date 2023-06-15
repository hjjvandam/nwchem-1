#!/bin/bash
../../../bin/LINUX64/nwchem 1fme_prepare.nw     2>&1 | tee 1fme_prepare.out
../../../bin/LINUX64/nwchem 1fme_minimize.nw    2>&1 | tee 1fme_minimize.out
cp nwchemdat_md.qrs nwchemdat_md.rst
../../../bin/LINUX64/nwchem 1fme_equilibrate.nw 2>&1 | tee 1fme_equilibrate.out
#../../../bin/LINUX64/nwchem 1fme_dynamics.nw    2>&1 | tee 1fme_dynamics.out
#../../../bin/LINUX64/nwchem 1fme_analysis.nw    2>&1 | tee 1fme_analysis.out

