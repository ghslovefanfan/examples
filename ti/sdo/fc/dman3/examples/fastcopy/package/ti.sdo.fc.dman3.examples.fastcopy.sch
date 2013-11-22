xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('ti.sdo.fc.dman3.examples.fastcopy');

/* ======== IMPORTS ======== */

    xdc.loadPackage('ti.bios');
    xdc.loadPackage('ti.sdo.fc.dman3');
    xdc.loadPackage('ti.sdo.fc.acpy3');
    xdc.loadPackage('ti.sdo.fc.utils');
    xdc.loadPackage('ti.sdo.fc.utils.api');
    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');

/* ======== OBJECTS ======== */

// package ti.sdo.fc.dman3.examples.fastcopy
    var pkg = $om.$$bind('ti.sdo.fc.dman3.examples.fastcopy.Package', $$PObj());
    $om.$$bind('ti.sdo.fc.dman3.examples.fastcopy', $$VObj('ti.sdo.fc.dman3.examples.fastcopy', pkg));

/* ======== CONSTS ======== */


/* ======== CREATES ======== */


/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */


/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package ti.sdo.fc.dman3.examples.fastcopy
    var po = $om['ti.sdo.fc.dman3.examples.fastcopy.Package'].$$init('ti.sdo.fc.dman3.examples.fastcopy.Package', $om['xdc.IPackage.Module']);
    var cap = $om.$$bind('xdc.IPackage$$capsule', xdc.loadCapsule('ti/sdo/fc/dman3/examples/fastcopy/package.xs'));
        if (cap['init']) po.$$fxn('init', $om['xdc.IPackage$$init'], cap['init']);
        if (cap['close']) po.$$fxn('close', $om['xdc.IPackage$$close'], cap['close']);
        if (cap['validate']) po.$$fxn('validate', $om['xdc.IPackage$$validate'], cap['validate']);
        if (cap['exit']) po.$$fxn('exit', $om['xdc.IPackage$$exit'], cap['exit']);
        if (cap['getLibs']) po.$$fxn('getLibs', $om['xdc.IPackage$$getLibs'], cap['getLibs']);
        if (cap['getSects']) po.$$fxn('getSects', $om['xdc.IPackage$$getSects'], cap['getSects']);
    po.$$bind('$capsule', cap);
    var pkg = $om['ti.sdo.fc.dman3.examples.fastcopy'].$$init(po, 'ti.sdo.fc.dman3.examples.fastcopy', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'ti.sdo.fc.dman3.examples.fastcopy');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'ti.sdo.fc.dman3.examples.fastcopy.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', []);
    pkg.$attr.$seal('length');
    pkg.$$bind('$imports', [
        ['ti.bios', []],
        ['ti.sdo.fc.dman3', []],
        ['ti.sdo.fc.acpy3', []],
        ['ti.sdo.fc.utils', []],
        ['ti.sdo.fc.utils.api', []],
    ]);
    if (pkg.$vers.length >= 3) {
        pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));
    }
    
    pkg.build.libraries = [
        'fcpy_ti.a64P',
    ];
    
    pkg.build.libDesc = [
        [
            'fcpy_ti.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
    ];

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    pkg.init();
