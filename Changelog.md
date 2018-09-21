Change Log
====================

All notable changes to the [QPF] software project will be documented in this file.

[V2.1rc1] / 2018-09-21
--------------------------

(This is the output of the log messages, must be organised)
Added tabbars and modified reprocessing dialog
Symlinks managmnt., task status spec. loading and qpfapp
Remove obsolete scripts
Add coverage options
Changed to install new qpfapp script
Cleaned up
Install qpfapp config file in folder HOME/.qpf
Modify qpfapp and included scripts to solve output in console
NEw dialog, icon and help function to request for user/password if needed
Changes to allow for some flags from HMI move to task to be created
Minor update of GRTAGS
Minor modification of master
Updates to send reprocessed products to VOSpace or IPython
UTs for module str
New getData() method for Json file handler class
New method setData for JSON based file handlers
UTs for filehdl package
UTs for str package
Preliminary setup for UTs for package uuid
UTs for filehdl package
UTs for InFix package
Add uptime for Core and HMI
New UTs for vos package
Basic creation of objects in UTs for fmk
Use return for VOS UTs
Avoid non finished UTs
Avoid unexisting sessions show messajes in stderr
Copy scripts in WA
Modifications to fix HOST suspend/stop/reactivate
Set agStatus to STOPPED only in case host STOP
Added nanomsg 1.0.0 package to source tree
New storage of QDT reports into archive, and filtering from HMI
Added name and specification to product query panels, and fix close tabs
Added modification to install scripts lib
Added function str::right()
Changed version to 2.1beta
Added D to obsmodes
Added the storage of the QLA report (first approach)
Update tasks status and refresh prod.mat.view
New icons
Changes to allow for some flags from HMI move to task to be created
Updates to send reprocessed products to VOSpace or IPython
UTs for module str
New getData() method for Json file handler class
Add uptime for Core and HMI
Modifications to fix HOST suspend/stop/reactivate
Merge from QPF/git after persistence-tests
Corrected errors of automatic merge from GIT
New set of UTs, and very minor modifications
Minor fixes for the installation process
Add switch_processors.sh bash script
Updated by lconversi to change also LE1 processor:
Updated to install harfbuzz-devel package and update main harfbuzz ones
Minimum correction
Fix usage message
Fix docker group creation
Last changes from Git repository
Separation betweek LE1 and QLA
Obsolete files
Last modifications from Git/uts
Last modifications from Git/uts (II)
Commented out test for the time being
Test sample3 split in 3a and 3b
Solved scrolling/selection of Local Archive View while updated
Set killed() comparison to false for Jenkins to work
Removed killed() comparison (return code not stable)

[V2.0] / 2018-03-07
--------------------------

First release candidate for the QPF V2.0.  The main changes with respect to
the previous version are:

### Improvements

- New messaging library Nanomsg used
- New messaging schema improves speed and scalability
- HTTP file server for Swarm services
- New monitoring view for Task Agents
- Improved way to define & configure data processors
- New WWW pages to show processing status
- Improved sorting of data products in local archive view
- Improved task processing monitoring
- Mongoose lib now part of source code
- Definition of processors now include command line call with arguments
  and Docker image
- Docker images now pulled from Nexus Docker Repository

### New Features

- Added Pause/Resume/Cancel task, and Suspend, Cancel host processing
- Retrieval and browsing of Processing alerts, and opening of source reports
- List System Alerts
- Reprocessed products can be placed in user defined area or external folders
- Reprocessed products can be stored in VOSpace user account
- Data products can be analysed with IPython

### Fixed

- Progress of tasks now reflects output provided in running tasks log
- Usage and definition of (external) User Defined Tools
- Fixed saving of configuration from ConfigTool

### Cosmetic changes

- New, improved ConfigTool entries distribution
- Minor updates to main HMI
- Big improvement to ConfigTool HMI

### Removed

- Some internal messages are replaced by direct component method calls
- Removed old 0MQ messaging library

----

[V1.2] / 2017-05-08
--------------------------

First release candidate for the QPF V1.2.  The main changes with respecto to the previous version are:

### Improvements

- Added new wrapper for parseFilename to simplify calls
- Modifications to add a filter panel to Alerts and Products listing
- Modifications to allow pre-set and custom filters on Products Archive view and Processing Alerts view

### New Features

- Internal database now uses enum for some integer fields
- Added euclid.h and new test file for FileNameSpec
- Added file and QDT report handlers

### Fixed

- Fixed minor issues when not in DEBUG mode
- Modified insert of record in products_info to use enum fields
- Corrected QDTReportHandler to catch also NISP issues
- Corrections to fix reset of custom filters on local archive table

### Cosmetic changes

- Modified release id and date

### Removed

----

[V1.1] / 2016-12-20
--------------------------

Release [V1.1] of the QPF.  The main changes are:

- Now the reference target Linux distribution is LODEEN 1.2.
- Now the integrated QPF application is split in two main components, the QPF Core and the QPF GUI
  + The QPF Core does all the job, but runs in the background with no visible user interface.
  + The QPF GUI is the new passive graphical user interface.
- The [QPF] is now installed together with the [QDT], following the procedure at [QPF & QDT Installation].
- A more complete configuration tool is presented, although is not yet fully functional.
- Improved scripts for building the applications and for the installation of the COTS.
- Included the files COPYING and COPYING.LESSER, containing the GPL and LGPL in text form.
- Included the license notice in the README.md file.

### Improvements

QPF Core:

- Now the Core reports an error if a config file is provided but does not exist.
- Updated version in version.h and VERSION files
- Changed INSTALL.md to point to Confluence installation procedure.
- Added main comment header to those source files without it.
- Now additional tasks can be coded for the execution in the run loop of each component.
- Now SIGINT is captured for a controlled shutting down.
- Main comment headers updated

QPF GUI:

- The list of open panels (tabs created showing the content of the different product files in the local archive) is now available.  With the right mouse button a context menu appears for closing all, the selected, or all but the selected element.  This list of panels is now shown in two places:
  + In a dedicated detachable docking window
  + In a combo box that appears when clicking in a button in the top left corner of the tabs bar.
- A more complete configuration tool is presented, although is not yet fully functional.

### New Features

- Improved Build script, which provides a BUILD_ID identifier for each build.

QPF Core:

- User Defined tools to open product files in the local archive.  They are part of the configuration and can be handled via the QPF GUI Config Tool.
- New script to start docker service.
- New PostgreSQL Database initialization script
- New PostgreSQL Server Start script
- New COTS Installation script for LODEEN installations

QPF GUI:

- New integrated JSON data viewer.

### Fixed

- Many bugs in the processing of the data and the handling of the input and output products are fixed.
- Retrieval and displaying of the status of the different components by the QPF GUI is now fixed.
- Solved issue with products left behind in gateway storage area.
- Solved bug in the handling of Task results messages.
- Components now do not transit to RUNNING when exiting from OPERATIONAL loop.
- Solved bugs in ClearForQPF.sh script.

### Cosmetic Changes

- A splash screen image is shown when
- An application icon is now shown in the main window at the top right corner.
- The fixed panels in the main window have now a small icon.

### Removed

- Removed entire integrated version of QPF Core and QPF GUI
- Now the Quit All commanded from the HMI is sent directly via CMD message to the EvtMng, not as a DB iCommand.

----

[V1.0] / 2016-04-22
--------------------

First official release of the [QPF].


----

[V2.0]: http://euclid.esac.esa.int/svn/ESA/SOC/SOC-3-DEV/SOC-3-07-QLook/QPF/tags/V2.0
[V1.2]: http://euclid.esac.esa.int/svn/ESA/SOC/SOC-3-DEV/SOC-3-07-QLook/QPF/tags/V1.2
[V1.1]: http://euclid.esac.esa.int/svn/ESA/SOC/SOC-3-DEV/SOC-3-07-QLook/QPF/tags/V1.1
[V1.0]: http://euclid.esac.esa.int/svn/ESA/SOC/SOC-3-DEV/SOC-3-07-QLook/QPF/tags/V1.0

[QPF & QDT Installation]: https://issues.cosmos.esa.int/euclidwiki/display/QLA/QLA+Processing+Framework+and+Diagnostic+Tool+Installation
[QPF]: https://issues.cosmos.esa.int/euclidwiki/pages/viewpage.action?pageId=4259980
[QDT]: https://issues.cosmos.esa.int/euclidwiki/pages/viewpage.action?pageId=4259917

<!--

Title:       Change Log
Subtitle:    Euclid QLA Processing Framework Change Log
Project:     QPF
Author:      J C Gonzalez
Affiliation: Euclid SOC Team @ ESAC - Telespazio Vega U.K. S.L.
Web:         http://www.cosmos.esa.int/web/euclid
Date:        2018-02-19

Copyright (C) 2015-2018  Euclid SOC Team @ ESAC

The format is based on [Keep a Changelog](http://keepachangelog.com/)
taking into account also [Semantic Versioning](http://semver.org/).

-->
