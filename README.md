# VS Code \ Secure Embedded Project `interprocess_communication`

## Overview
This repository builds ELF files from Open CMSIS Pack build tool, aka. CMSIS-Toolbox.

## Recommended Configuration for Git
To configure Git to handle line endings not to automatically do effective CR/LF wrap for each OS system on local. For more information, see [git-config](https://git-scm.com/docs/git-config).
```
git clone --recursive --no-checkout https://github.com/chipwon-ocp/interprocess_communication.git
```
```
git config --global core.autocrlf false
```
```
git config core.eol lf
```
Next do checkout.

## Build Solution/Project
Use the `cbuild` command from CMSIS-Toolbox to generate and build one or all configurations of the solution.
Find out which `contexts` are specified by the solution.
```
cbuild list contexts kickoff.csolution.yml
```
Build the context set as selected in the CMSIS extension tab.
```
cbuild kickoff.csolution.yml --context-set --packs --update-rte --rebuild
```
