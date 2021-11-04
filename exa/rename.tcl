#!/usr/bin/env tclsh

proc readtext fn { #<<<
	set h	[open $fn r]
	try {chan configure $h -encoding utf-8; read $h} finally {close $h}
}

#>>>
proc writetext {fn chars} { #<<<
	set h	[open $fn w]
	try {chan configure $h -encoding utf-8; puts -nonewline $h $chars} finally {close $h}
}

#>>>

set newname	[lindex $argv 0]
if {$newname eq ""} {
	puts stderr "Usage: $::argv0 newname"
	puts stderr "Replace all instances of \"dedup\" with case-appropriate versions of \$newname"
	exit 1
}

set map	[list \
	dedup		[string tolower $newname] \
	Dedup		[string totitle $newname] \
	DEDUP		[string toupper $newname] \
]

proc process_filename from { #<<<
	global map
	set dir		[file dirname [file normalize $from]]
	set tail	[file tail $from]
	set to		[string map $map $tail]
	set fqto	[file join $dir $to]
	if {$tail ne $to} {
		puts "Renaming $from -> $fqto"
		file rename $from $fqto
	}
	set fqto
}

#>>>

set targets	[glob [file dirname [file normalize [info script]]]/*]
while {[llength $targets]} {
	set targets	[lassign $targets[unset targets] e]

	if {[file isdirectory $e]} {
		set newname	[process_filename $e]
		lappend targets {*}[glob -nocomplain $newname/*]
	} else {
		if {[file type $e] eq "link"} {
			# Only transform the name
			process_filename $e
		} else {
			puts "Replacing strings in $e"
			writetext $e [string map $map [readtext $e]]
			process_filename $e
		}
	}
}


# vim: foldmethod=marker foldmarker=<<<,>>> ts=4 shiftwidth=4
