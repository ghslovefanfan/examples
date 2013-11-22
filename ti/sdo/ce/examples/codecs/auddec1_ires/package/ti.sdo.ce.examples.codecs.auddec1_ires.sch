xdc.loadCapsule('xdc/om2.xs');

var $om = xdc.om;
var __CFG__ = $om.$name == 'cfg';
var __ROV__ = $om.$name == 'rov';
var $$pkgspec = xdc.$$ses.findPkg('ti.sdo.ce.examples.codecs.auddec1_ires');

/* ======== IMPORTS ======== */

    xdc.loadPackage('ti.sdo.fc.ires.examples.codecs.auddec1');
    xdc.loadPackage('xdc');
    xdc.loadPackage('xdc.corevers');
    xdc.loadPackage('ti.sdo.ce.audio1');

/* ======== OBJECTS ======== */

// package ti.sdo.ce.examples.codecs.auddec1_ires
    var pkg = $om.$$bind('ti.sdo.ce.examples.codecs.auddec1_ires.Package', $$PObj());
    $om.$$bind('ti.sdo.ce.examples.codecs.auddec1_ires', $$VObj('ti.sdo.ce.examples.codecs.auddec1_ires', pkg));
// module AUDDEC1_IRES
    var po = $om.$$bind('ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES.Module', $$PObj());
    var vo = $om.$$bind('ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES', $$VObj('ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES', po));
    pkg.$$bind('AUDDEC1_IRES', vo);

/* ======== CONSTS ======== */

// module AUDDEC1_IRES

/* ======== CREATES ======== */

// module AUDDEC1_IRES

/* ======== FUNCTIONS ======== */


/* ======== SIZES ======== */


/* ======== TYPES ======== */

// module AUDDEC1_IRES
    var cap = $om.$$bind('ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES$$capsule', xdc.loadCapsule('ti/sdo/ce/examples/codecs/auddec1_ires/AUDDEC1_IRES.xs'));
    var po = $om['ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES.Module'].$$init('ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES.Module', $om['ti.sdo.ce.audio1.IAUDDEC1.Module']);
        po.$$fld('$hostonly', $$T_Num, 1, 'r');
        po.$$fld('ialgFxns', $$T_Str, "AUDDEC1_TI_AUDDECIRES", 'rh');
        po.$$fld('iresFxns', $$T_Str, "AUDDEC1_TI_IRES", 'rh');
        var fxn = cap['module$meta$init'];
        if (fxn) $om.$$bind('ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES$$module$meta$init', true);
        if (fxn) po.$$fxn('module$meta$init', $$T_Met, fxn);
        if (cap['getCreationStackSize']) po.$$fxn('getCreationStackSize', $om['ti.sdo.ce.ICodec$$getCreationStackSize'], cap['getCreationStackSize']);
        if (cap['getDaramScratchSize']) po.$$fxn('getDaramScratchSize', $om['ti.sdo.ce.ICodec$$getDaramScratchSize'], cap['getDaramScratchSize']);
        if (cap['getSaramScratchSize']) po.$$fxn('getSaramScratchSize', $om['ti.sdo.ce.ICodec$$getSaramScratchSize'], cap['getSaramScratchSize']);
        if (cap['getStackSize']) po.$$fxn('getStackSize', $om['ti.sdo.ce.ICodec$$getStackSize'], cap['getStackSize']);
        if (cap['getUUID']) po.$$fxn('getUUID', $om['ti.sdo.ce.ICodec$$getUUID'], cap['getUUID']);

/* ======== ROV ======== */

if (__ROV__) {


} // __ROV__

/* ======== SINGLETONS ======== */

// package ti.sdo.ce.examples.codecs.auddec1_ires
    var po = $om['ti.sdo.ce.examples.codecs.auddec1_ires.Package'].$$init('ti.sdo.ce.examples.codecs.auddec1_ires.Package', $om['xdc.IPackage.Module']);
    var cap = $om.$$bind('xdc.IPackage$$capsule', xdc.loadCapsule('ti/sdo/ce/examples/codecs/auddec1_ires/package.xs'));
        if (cap['init']) po.$$fxn('init', $om['xdc.IPackage$$init'], cap['init']);
        if (cap['close']) po.$$fxn('close', $om['xdc.IPackage$$close'], cap['close']);
        if (cap['validate']) po.$$fxn('validate', $om['xdc.IPackage$$validate'], cap['validate']);
        if (cap['exit']) po.$$fxn('exit', $om['xdc.IPackage$$exit'], cap['exit']);
        if (cap['getLibs']) po.$$fxn('getLibs', $om['xdc.IPackage$$getLibs'], cap['getLibs']);
        if (cap['getSects']) po.$$fxn('getSects', $om['xdc.IPackage$$getSects'], cap['getSects']);
    po.$$bind('$capsule', cap);
    var pkg = $om['ti.sdo.ce.examples.codecs.auddec1_ires'].$$init(po, 'ti.sdo.ce.examples.codecs.auddec1_ires', $$DEFAULT, false);
    $om.$packages.$add(pkg);
    pkg.$$bind('$name', 'ti.sdo.ce.examples.codecs.auddec1_ires');
    pkg.$$bind('$category', 'Package');
    pkg.$$bind('$$qn', 'ti.sdo.ce.examples.codecs.auddec1_ires.');
    pkg.$$bind('$spec', $$pkgspec);
    pkg.$$bind('$vers', []);
    pkg.$attr.$seal('length');
    pkg.$$bind('$imports', [
        ['ti.sdo.fc.ires.examples.codecs.auddec1', []],
    ]);
    if (pkg.$vers.length >= 3) {
        pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));
    }
    
    pkg.build.libraries = [
    ];
    
    pkg.build.libDesc = [
    ];
// module AUDDEC1_IRES
    var vo = $om['ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES'];
    var po = $om['ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES.Module'];
    vo.$$init(po, 'ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES', $$DEFAULT, false);
    vo.$$bind('Module', po);
    vo.$$bind('$category', 'Module');
    vo.$$bind('$spec', xdc.$$ses.findUnit('ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES'));
    vo.$$bind('$capsule', $om['ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES$$capsule']);
    vo.$$bind('$package', $om['ti.sdo.ce.examples.codecs.auddec1_ires']);
    vo.$$bind('$$tdefs', []);
    vo.$$bind('$$proxies', []);
    vo.$$bind('$$mcfgs', []);
    pkg.$modules.$add(vo);
    $om.$modules.$add(vo);
    vo.$$bind('$$instflag', 0);
    vo.$$bind('$$iobjflag', 1);
    vo.$$bind('$$sizeflag', 1);
    vo.$$bind('$$dlgflag', 0);
    vo.$$bind('$$iflag', 1);
    vo.$$bind('$$romcfgs', '');
    if ('Module_State' in vo) vo.$$bind('$object', new vo.Module_State);
    vo.$$bind('$$meta_iobj', 0 + ('ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES$$instance$static$init' in $om));
    vo.$$bind('$$fxntab', []);
    vo.$$bind('$$logEvtCfgs', []);
    vo.$$bind('$$errorDescCfgs', []);
    vo.$$bind('$$assertDescCfgs', []);
    vo.$attr.$seal('length');
    pkg.$$bind('AUDDEC1_IRES', vo);
    pkg.$unitNames.$add('AUDDEC1_IRES');

/* ======== INITIALIZATION ======== */

if (__CFG__) {
} // __CFG__
    $om['ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES'].module$meta$init();
    pkg.init();
    $om['ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES'].$$bless();
