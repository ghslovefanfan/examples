xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446');

/* ======== IMPORTS ======== */

    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');

/* ======== OBJECTS ======== */

// package ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446
    var pkg = $om.$$bind('ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446.Package', $$PObj());
    $om.$$bind('ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446', $$VObj('ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446', pkg));

/* ======== CONSTS ======== */


/* ======== CREATES ======== */


/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */


/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446
    var po = $om['ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446.Package'].$$init('ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446.Package', $om['xdc.IPackage.Module']);
    po.$$bind('$capsule', undefined);
    var pkg = $om['ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446'].$$init(po, 'ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'ti.sdo.ce.examples.apps.audio_copy.dualcpu.evmDM6446.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', [1, 0, 0]);
    pkg.$attr.$seal('length');
    pkg.$$bind('$imports', [
    ]);
    if (pkg.$vers.length >= 3) {
        pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));
    }
    
    pkg.build.libraries = [
    ];
    
    pkg.build.libDesc = [
    ];

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    pkg.init();
