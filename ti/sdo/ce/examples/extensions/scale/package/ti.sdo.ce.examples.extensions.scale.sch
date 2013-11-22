xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('ti.sdo.ce.examples.extensions.scale');

/* ======== IMPORTS ======== */

    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');
    xdc.loadPackage('ti.sdo.ce');

/* ======== OBJECTS ======== */

// package ti.sdo.ce.examples.extensions.scale
    var pkg = $om.$$bind('ti.sdo.ce.examples.extensions.scale.Package', $$PObj());
    $om.$$bind('ti.sdo.ce.examples.extensions.scale', $$VObj('ti.sdo.ce.examples.extensions.scale', pkg));
// interface ISCALE
    var po = $om.$$bind('ti.sdo.ce.examples.extensions.scale.ISCALE.Module', $$PObj());
    var vo = $om.$$bind('ti.sdo.ce.examples.extensions.scale.ISCALE', $$VObj('ti.sdo.ce.examples.extensions.scale.ISCALE', po));
    pkg.$$bind('ISCALE', vo);

/* ======== CONSTS ======== */

// interface ISCALE

/* ======== CREATES ======== */

// interface ISCALE

/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */

// interface ISCALE
    var po = $om['ti.sdo.ce.examples.extensions.scale.ISCALE.Module'].$$init('ti.sdo.ce.examples.extensions.scale.ISCALE.Module', $om['ti.sdo.ce.ICodec.Module']);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('serverFxns', $$T_Str, "SCALE_SKEL", 'rh');
        po.$$fld('stubFxns', $$T_Str, "SCALE_STUBS", 'rh');
        po.$$fld('rpcProtocolVersion', $$T_CNum('(xdc_Int)'), 1, 'rh');

/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package ti.sdo.ce.examples.extensions.scale
    var po = $om['ti.sdo.ce.examples.extensions.scale.Package'].$$init('ti.sdo.ce.examples.extensions.scale.Package', $om['xdc.IPackage.Module']);
    var cap = $om.$$bind('xdc.IPackage$$capsule', xdc.loadCapsule('ti/sdo/ce/examples/extensions/scale/package.xs'));
        if (cap['init']) po.$$fxn('init', $om['xdc.IPackage$$init'], cap['init']);
        if (cap['close']) po.$$fxn('close', $om['xdc.IPackage$$close'], cap['close']);
        if (cap['validate']) po.$$fxn('validate', $om['xdc.IPackage$$validate'], cap['validate']);
        if (cap['exit']) po.$$fxn('exit', $om['xdc.IPackage$$exit'], cap['exit']);
        if (cap['getLibs']) po.$$fxn('getLibs', $om['xdc.IPackage$$getLibs'], cap['getLibs']);
        if (cap['getSects']) po.$$fxn('getSects', $om['xdc.IPackage$$getSects'], cap['getSects']);
    po.$$bind('$capsule', cap);
    var pkg = $om['ti.sdo.ce.examples.extensions.scale'].$$init(po, 'ti.sdo.ce.examples.extensions.scale', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'ti.sdo.ce.examples.extensions.scale');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'ti.sdo.ce.examples.extensions.scale.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', []);
    pkg.$attr.$seal('length');
    pkg.$$bind('$imports', [
    ]);
    if (pkg.$vers.length >= 3) {
        pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));
    }
    
    pkg.build.libraries = [
        'lib/scale_debug.a470MV',
        'lib/scale_debug.a64P',
        'lib/scale.a64P',
        'lib/scale.a470MV',
    ];
    
    pkg.build.libDesc = [
        [
            'lib/scale_debug.a470MV',
            {
                target: 'gnu.targets.MVArm9'
            }
        ],
        [
            'lib/scale_debug.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/scale.a64P',
            {
                target: 'ti.targets.C64P'
            }
        ],
        [
            'lib/scale.a470MV',
            {
                target: 'gnu.targets.MVArm9'
            }
        ],
    ];
// interface ISCALE
    var vo = $om['ti.sdo.ce.examples.extensions.scale.ISCALE'];
    var po = $om['ti.sdo.ce.examples.extensions.scale.ISCALE.Module'];
    vo.$$init(po, 'ti.sdo.ce.examples.extensions.scale.ISCALE', $$DEFAULT, false);
    vo.$$bind('Module', po);
    vo.$$bind('$category', 'Interface');
    vo.$$bind('$spec', xdc.$$ses.findUnit('ti.sdo.ce.examples.extensions.scale.ISCALE'));
    vo.$$bind('$capsule', undefined);
    vo.$$bind('$package', $om['ti.sdo.ce.examples.extensions.scale']);
    vo.$$bind('$$tdefs', []);
    vo.$$bind('$$proxies', []);
    pkg.$interfaces.$add(vo);
    pkg.$$bind('ISCALE', vo);
    pkg.$unitNames.$add('ISCALE');
    vo.$seal();

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    pkg.init();
    $om['ti.sdo.ce.examples.extensions.scale.ISCALE'].$$bless();
