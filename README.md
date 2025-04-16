EXPORTING STUBS FROM AN EXTENSION
=================================

The stubs mechanism used by Tcl is great, and easy to use for extensions to
link against Tcl in a version-portable way.  While the mechanism exists for
extension authors to provide their own stubs APIs for other extensions to link
against and use, the documentation available is incomplete or wrong, and every
extension I can find that has tried to use it is full of errors or hacks, other
than the reference example of Tk, or TclOO / dict, which don't follow the 
pattern laid out in TEA for this.

These are a collection of fairly minimal extensions that export and use their
own stubs APIs, in the least broken and hacky ways I could find, so that I
don't have to go through the experience of figuring all this stuff out again
from broken examples.

I haven't even attempted to get the magic working for the Windows platform,
as I don't have access to a build environment for it.  If you have the
unfortunate requirement to make this work on Windows, and succeed in modifing
these examples to do that, a pull request will be welcomed.

Exa
---
This extension exports a stubs API (and only that - no Tcl commands are
defined by the extension).

Exb
---
This extension links against the Exa stubs library and calls its API.
Autoconf magic handles linking to the Exa stubs, driven from the --with-exa=
configure setting.

Exc
---
This extension parallels Exa's code, but without exporting a stubs API,
so it much more closely matches the layout of the sampleextension.  It is
intended to serve as a comparison to Exa to see what needs to change / be
added to export stubs from an extension.

Tclconfig
---------
These examples don't bake in tclconfig - clone the tclconfig head from
https://core.tcl-lang.org/tclconfig and symlink tclconfig from each
extension's root to it in order to build them.
