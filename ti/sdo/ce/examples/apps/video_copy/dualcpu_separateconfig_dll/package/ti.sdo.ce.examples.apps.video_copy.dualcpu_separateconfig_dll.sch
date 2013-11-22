xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll');

/* ======== IMPORTS ======== */

    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');

/* ======== OBJECTS ======== */

// package ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll
    var pkg = $om.$$bind('ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll.Package', $$PObj());
    $om.$$bind('ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll', $$VObj('ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll', pkg));

/* ======== CONSTS ======== */


/* ======== CREATES ======== */


/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */


/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll
    var po = $om['ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll.Package'].$$init('ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll.Package', $om['xdc.IPackage.Module']);
    po.$$bind('$capsule', undefined);
    var pkg = $om['ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll'].$$init(po, 'ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'ti.sdo.ce.examples.apps.video_copy.dualcpu_separateconfig_dll.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', []);
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
