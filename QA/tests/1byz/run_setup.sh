#!/bin/bash
../../../bin/LINUX64/nwchem 1byz_prepare.nw     2>&1 | tee 1byz_prepare.out
../../../bin/LINUX64/nwchem 1byz_minimize.nw    2>&1 | tee 1byz_minimize.out
cp nwchemdat_md.qrs nwchemdat_md.rst
../../../bin/LINUX64/nwchem 1byz_equilibrate.nw 2>&1 | tee 1byz_equilibrate.out
../../../bin/LINUX64/nwchem 1byz_dynamics.nw    2>&1 | tee 1byz_dynamics.out
../../../bin/LINUX64/nwchem 1byz_analysis.nw    2>&1 | tee 1byz_analysis.out

