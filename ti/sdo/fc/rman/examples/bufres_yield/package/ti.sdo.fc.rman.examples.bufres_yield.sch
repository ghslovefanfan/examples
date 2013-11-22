xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('ti.sdo.fc.rman.examples.bufres_yield');

/* ======== IMPORTS ======== */

    xdc.loadPackage('ti.bios');
    xdc.loadPackage('ti.sdo.fc.utils');
    xdc.loadPackage('ti.sdo.fc.dskt2');
    xdc.loadPackage('ti.sdo.fc.utils.api');
    xdc.loadPackage('ti.sdo.fc.rman');
    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');

/* ======== OBJECTS ======== */

// package ti.sdo.fc.rman.examples.bufres_yield
    var pkg = $om.$$bind('ti.sdo.fc.rman.examples.bufres_yield.Package', $$PObj());
    $om.$$bind('ti.sdo.fc.rman.examples.bufres_yield', $$VObj('ti.sdo.fc.rman.examples.bufres_yield', pkg));

/* ======== CONSTS ======== */


/* ======== CREATES ======== */


/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */


/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package ti.sdo.fc.rman.examples.bufres_yield
    var po = $om['ti.sdo.fc.rman.examples.bufres_yield.Package'].$$init('ti.sdo.fc.rman.examples.bufres_yield.Package', $om['xdc.IPackage.Module']);
    var cap = $om.$$bind('xdc.IPackage$$capsule', xdc.loadCapsule('ti/sdo/fc/rman/examples/bufres_yield/package.xs'));
        if (cap['init']) po.$$fxn('init', $om['xdc.IPackage$$init'], cap['init']);
        if (cap['close']) po.$$fxn('close', $om['xdc.IPackage$$close'], cap['close']);
        if (cap['validate']) po.$$fxn('validate', $om['xdc.IPackage$$validate'], cap['validate']);
        if (cap['exit']) po.$$fxn('exit', $om['xdc.IPackage$$exit'], cap['exit']);
        if (cap['getLibs']) po.$$fxn('getLibs', $om['xdc.IPackage$$getLibs'], cap['getLibs']);
        if (cap['getSects']) po.$$fxn('getSects', $om['xdc.IPackage$$getSects'], cap['getSects']);
    po.$$bind('$capsule', cap);
    var pkg = $om['ti.sdo.fc.rman.examples.bufres_yield'].$$init(po, 'ti.sdo.fc.rman.examples.bufres_yield', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'ti.sdo.fc.rman.examples.bufres_yield');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'ti.sdo.fc.rman.examples.bufres_yield.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', [1, 0, 0]);
    pkg.$attr.$seal('length');
    pkg.$$bind('$imports', [
        ['ti.bios', []],
        ['ti.sdo.fc.utils', []],
        ['ti.sdo.fc.dskt2', []],
        ['ti.sdo.fc.utils.api', []],
        ['ti.sdo.fc.rman', []],
    ]);
    if (pkg.$vers.length >= 3) {
        pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));
    }
    
    pkg.build.libraries = [
        'bufres.a64P',
        'bufalg_ti.a64P',
    ];
    
    pkg.build.libDesc = [
        [
            'bufres.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'bufalg_ti.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
    ];

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    pkg.init();
