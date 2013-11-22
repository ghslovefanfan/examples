xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('ti.sdo.fc.ires.examples.codecs.template');

/* ======== IMPORTS ======== */

    xdc.loadPackage('ti.sdo.fc.ires.nullresource');
    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');

/* ======== OBJECTS ======== */

// package ti.sdo.fc.ires.examples.codecs.template
    var pkg = $om.$$bind('ti.sdo.fc.ires.examples.codecs.template.Package', $$PObj());
    $om.$$bind('ti.sdo.fc.ires.examples.codecs.template', $$VObj('ti.sdo.fc.ires.examples.codecs.template', pkg));

/* ======== CONSTS ======== */


/* ======== CREATES ======== */


/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */


/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package ti.sdo.fc.ires.examples.codecs.template
    var po = $om['ti.sdo.fc.ires.examples.codecs.template.Package'].$$init('ti.sdo.fc.ires.examples.codecs.template.Package', $om['xdc.IPackage.Module']);
    var cap = $om.$$bind('xdc.IPackage$$capsule', xdc.loadCapsule('ti/sdo/fc/ires/examples/codecs/template/package.xs'));
        if (cap['init']) po.$$fxn('init', $om['xdc.IPackage$$init'], cap['init']);
        if (cap['close']) po.$$fxn('close', $om['xdc.IPackage$$close'], cap['close']);
        if (cap['validate']) po.$$fxn('validate', $om['xdc.IPackage$$validate'], cap['validate']);
        if (cap['exit']) po.$$fxn('exit', $om['xdc.IPackage$$exit'], cap['exit']);
        if (cap['getLibs']) po.$$fxn('getLibs', $om['xdc.IPackage$$getLibs'], cap['getLibs']);
        if (cap['getSects']) po.$$fxn('getSects', $om['xdc.IPackage$$getSects'], cap['getSects']);
    po.$$bind('$capsule', cap);
    var pkg = $om['ti.sdo.fc.ires.examples.codecs.template'].$$init(po, 'ti.sdo.fc.ires.examples.codecs.template', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'ti.sdo.fc.ires.examples.codecs.template');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'ti.sdo.fc.ires.examples.codecs.template.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', [1, 0, 0]);
    pkg.$attr.$seal('length');
    pkg.$$bind('$imports', [
        ['ti.sdo.fc.ires.nullresource', []],
    ]);
    if (pkg.$vers.length >= 3) {
        pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));
    }
    
    pkg.build.libraries = [
        'lib/debug/template_ti.a55L',
        'lib/template_ti.a55L',
        'lib/debug/template_ti.a86U',
        'lib/template_ti.a86U',
        'lib/template_ti.a470MV',
        'lib/debug/template_ti.a64P',
        'lib/template_ti.a64P',
        'lib/template_ti.a470uC',
        'lib/debug/template_ti.a470MV',
        'lib/debug/template_ti.a470uC',
    ];
    
    pkg.build.libDesc = [
        [
            'lib/debug/template_ti.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/template_ti.a55L',
            {
                target: 'ti.targets.C55_large'
            }
        ],
        [
            'lib/debug/template_ti.a86U',
            {
                target: 'gnu.targets.Linux86'
            }
        ],
        [
            'lib/template_ti.a86U',
            {
                target: 'gnu.targets.Linux86'
            }
        ],
        [
            'lib/template_ti.a470MV',
            {
                target: 'gnu.targets.MVArm9'
            }
        ],
        [
            'lib/debug/template_ti.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/template_ti.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/template_ti.a470uC',
            {
                target: 'gnu.targets.UCArm9'
            }
        ],
        [
            'lib/debug/template_ti.a470MV',
            {
                target: 'gnu.targets.MVArm9'
            }
        ],
        [
            'lib/debug/template_ti.a470uC',
            {
                target: 'gnu.targets.UCArm9'
            }
        ],
    ];

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    pkg.init();
