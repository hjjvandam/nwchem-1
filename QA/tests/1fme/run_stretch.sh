#!/bin/bash
../../../bin/LINUX64/nwchem 1fme_prepare_restrain.nw     2>&1 | tee 1fme_prepare_restrain.out
../../../bin/LINUX64/nwchem 1fme_minimize_restrain.nw    2>&1 | tee 1fme_minimize_restrain.out
cp nwchemdat_md.qrs nwchemdat_md.rst
../../../bin/LINUX64/nwchem 1fme_dynamics_restrain.nw    2>&1 | tee 1fme_dynamics_restrain.out
../../../bin/LINUX64/nwchem 1fme_analysis.nw             2>&1 | tee 1fme_analysis.out

