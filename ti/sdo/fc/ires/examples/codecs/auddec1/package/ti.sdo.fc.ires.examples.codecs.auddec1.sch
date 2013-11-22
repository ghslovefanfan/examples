xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('ti.sdo.fc.ires.examples.codecs.auddec1');

/* ======== IMPORTS ======== */

    xdc.loadPackage('ti.sdo.fc.ires.bufres');
    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');

/* ======== OBJECTS ======== */

// package ti.sdo.fc.ires.examples.codecs.auddec1
    var pkg = $om.$$bind('ti.sdo.fc.ires.examples.codecs.auddec1.Package', $$PObj());
    $om.$$bind('ti.sdo.fc.ires.examples.codecs.auddec1', $$VObj('ti.sdo.fc.ires.examples.codecs.auddec1', pkg));

/* ======== CONSTS ======== */


/* ======== CREATES ======== */


/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */


/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package ti.sdo.fc.ires.examples.codecs.auddec1
    var po = $om['ti.sdo.fc.ires.examples.codecs.auddec1.Package'].$$init('ti.sdo.fc.ires.examples.codecs.auddec1.Package', $om['xdc.IPackage.Module']);
    var cap = $om.$$bind('xdc.IPackage$$capsule', xdc.loadCapsule('ti/sdo/fc/ires/examples/codecs/auddec1/package.xs'));
        if (cap['init']) po.$$fxn('init', $om['xdc.IPackage$$init'], cap['init']);
        if (cap['close']) po.$$fxn('close', $om['xdc.IPackage$$close'], cap['close']);
        if (cap['validate']) po.$$fxn('validate', $om['xdc.IPackage$$validate'], cap['validate']);
        if (cap['exit']) po.$$fxn('exit', $om['xdc.IPackage$$exit'], cap['exit']);
        if (cap['getLibs']) po.$$fxn('getLibs', $om['xdc.IPackage$$getLibs'], cap['getLibs']);
        if (cap['getSects']) po.$$fxn('getSects', $om['xdc.IPackage$$getSects'], cap['getSects']);
    po.$$bind('$capsule', cap);
    var pkg = $om['ti.sdo.fc.ires.examples.codecs.auddec1'].$$init(po, 'ti.sdo.fc.ires.examples.codecs.auddec1', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'ti.sdo.fc.ires.examples.codecs.auddec1');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'ti.sdo.fc.ires.examples.codecs.auddec1.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', [1, 0, 0]);
    pkg.$attr.$seal('length');
    pkg.$$bind('$imports', [
        ['ti.sdo.fc.ires.bufres', []],
    ]);
    if (pkg.$vers.length >= 3) {
        pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));
    }
    
    pkg.build.libraries = [
        'lib/debug/auddec1_ti.a64P',
        'lib/debug/auddec1_ti.a470MV',
        'lib/debug/auddec1_ti.a470uC',
        'lib/auddec1_ti.a470MV',
        'lib/auddec1_ti.a64P',
        'lib/debug/auddec1_ti.a55L',
        'lib/auddec1_ti.a470uC',
        'lib/debug/auddec1_ti.a86U',
        'lib/auddec1_ti.a55L',
        'lib/auddec1_ti.a86U',
    ];
    
    pkg.build.libDesc = [
        [
            'lib/debug/auddec1_ti.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/debug/auddec1_ti.a470MV',
            {
                target: 'gnu.targets.MVArm9'
            }
        ],
        [
            'lib/debug/auddec1_ti.a470uC',
            {
                target: 'gnu.targets.UCArm9'
            }
        ],
        [
            'lib/auddec1_ti.a470MV',
            {
                target: 'gnu.targets.MVArm9'
            }
        ],
        [
            'lib/auddec1_ti.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/debug/auddec1_ti.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/auddec1_ti.a470uC',
            {
                target: 'gnu.targets.UCArm9'
            }
        ],
        [
            'lib/debug/auddec1_ti.a86U',
            {
                target: 'gnu.targets.Linux86'
            }
        ],
        [
            'lib/auddec1_ti.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/auddec1_ti.a86U',
            {
                target: 'gnu.targets.Linux86'
            }
        ],
    ];

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    pkg.init();
