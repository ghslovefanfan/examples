#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = ti.targets.C64P{1,0,6.0,16
#
ifneq (clean,$(MAKECMDGOALS))
-include package/lib/lib/videnc_copy/package/package_ti.sdo.ce.examples.codecs.videnc_copy.o64P.dep
endif

package/lib/lib/videnc_copy/package/package_ti.sdo.ce.examples.codecs.videnc_copy.o64P: | .interfaces
package/lib/lib/videnc_copy/package/package_ti.sdo.ce.examples.codecs.videnc_copy.o64P: package/package_ti.sdo.ce.examples.codecs.videnc_copy.c lib/videnc_copy.a64P.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl64P $< ...
	$(ti.targets.C64P.rootDir)/bin/cl6x -c  -oe -qq -pdsw225 -pden -pds=195  -mv64p -eo.o64P -ea.s64P  -D__xdc_bld_pkg_c__=package.bld.c -Dxdc_target_name__=C64P -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_6_0_16 -o2   $(XDCINCS) -I$(ti.targets.C64P.rootDir)/include -fs=./package/lib/lib/videnc_copy/package -fr=./package/lib/lib/videnc_copy/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/videnc_copy/package -s o64P $< -C   -oe -qq -pdsw225 -pden -pds=195  -mv64p -eo.o64P -ea.s64P  -D__xdc_bld_pkg_c__=package.bld.c -Dxdc_target_name__=C64P -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_6_0_16 -o2   $(XDCINCS) -I$(ti.targets.C64P.rootDir)/include -fs=./package/lib/lib/videnc_copy/package -fr=./package/lib/lib/videnc_copy/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/videnc_copy/package/package_ti.sdo.ce.examples.codecs.videnc_copy.o64P:C_DIR=
package/lib/lib/videnc_copy/package/package_ti.sdo.ce.examples.codecs.videnc_copy.o64P: PATH:=$(ti.targets.C64P.rootDir)/bin/:$(PATH)

package/lib/lib/videnc_copy/package/package_ti.sdo.ce.examples.codecs.videnc_copy.s64P: | .interfaces
package/lib/lib/videnc_copy/package/package_ti.sdo.ce.examples.codecs.videnc_copy.s64P: package/package_ti.sdo.ce.examples.codecs.videnc_copy.c lib/videnc_copy.a64P.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl64P -n $< ...
	$(ti.targets.C64P.rootDir)/bin/cl6x -c -n -s -oe -qq -pdsw225 -pden -pds=195  -mv64p -eo.o64P -ea.s64P  -D__xdc_bld_pkg_c__=package.bld.c -Dxdc_target_name__=C64P -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_6_0_16 -o2   $(XDCINCS) -I$(ti.targets.C64P.rootDir)/include -fs=./package/lib/lib/videnc_copy/package -fr=./package/lib/lib/videnc_copy/package -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/videnc_copy/package -s o64P $< -C  -n -s -oe -qq -pdsw225 -pden -pds=195  -mv64p -eo.o64P -ea.s64P  -D__xdc_bld_pkg_c__=package.bld.c -Dxdc_target_name__=C64P -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_6_0_16 -o2   $(XDCINCS) -I$(ti.targets.C64P.rootDir)/include -fs=./package/lib/lib/videnc_copy/package -fr=./package/lib/lib/videnc_copy/package
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/videnc_copy/package/package_ti.sdo.ce.examples.codecs.videnc_copy.s64P:C_DIR=
package/lib/lib/videnc_copy/package/package_ti.sdo.ce.examples.codecs.videnc_copy.s64P: PATH:=$(ti.targets.C64P.rootDir)/bin/:$(PATH)

ifneq (clean,$(MAKECMDGOALS))
-include package/lib/lib/videnc_copy/videnc_copy.o64P.dep
endif

package/lib/lib/videnc_copy/videnc_copy.o64P: | .interfaces
package/lib/lib/videnc_copy/videnc_copy.o64P: videnc_copy.c lib/videnc_copy.a64P.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl64P $< ...
	$(ti.targets.C64P.rootDir)/bin/cl6x -c  -oe -qq -pdsw225 -pden -pds=195  -mv64p -eo.o64P -ea.s64P  -Dxdc_target_name__=C64P -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_6_0_16 -o2   $(XDCINCS) -I$(ti.targets.C64P.rootDir)/include -fs=./package/lib/lib/videnc_copy -fr=./package/lib/lib/videnc_copy -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/videnc_copy -s o64P $< -C   -oe -qq -pdsw225 -pden -pds=195  -mv64p -eo.o64P -ea.s64P  -Dxdc_target_name__=C64P -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_6_0_16 -o2   $(XDCINCS) -I$(ti.targets.C64P.rootDir)/include -fs=./package/lib/lib/videnc_copy -fr=./package/lib/lib/videnc_copy
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/videnc_copy/videnc_copy.o64P:C_DIR=
package/lib/lib/videnc_copy/videnc_copy.o64P: PATH:=$(ti.targets.C64P.rootDir)/bin/:$(PATH)

package/lib/lib/videnc_copy/videnc_copy.s64P: | .interfaces
package/lib/lib/videnc_copy/videnc_copy.s64P: videnc_copy.c lib/videnc_copy.a64P.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl64P -n $< ...
	$(ti.targets.C64P.rootDir)/bin/cl6x -c -n -s -oe -qq -pdsw225 -pden -pds=195  -mv64p -eo.o64P -ea.s64P  -Dxdc_target_name__=C64P -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_6_0_16 -o2   $(XDCINCS) -I$(ti.targets.C64P.rootDir)/include -fs=./package/lib/lib/videnc_copy -fr=./package/lib/lib/videnc_copy -fc $<
	$(MKDEP) -a $@.dep -p package/lib/lib/videnc_copy -s o64P $< -C  -n -s -oe -qq -pdsw225 -pden -pds=195  -mv64p -eo.o64P -ea.s64P  -Dxdc_target_name__=C64P -Dxdc_target_types__=ti/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_6_0_16 -o2   $(XDCINCS) -I$(ti.targets.C64P.rootDir)/include -fs=./package/lib/lib/videnc_copy -fr=./package/lib/lib/videnc_copy
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/videnc_copy/videnc_copy.s64P:C_DIR=
package/lib/lib/videnc_copy/videnc_copy.s64P: PATH:=$(ti.targets.C64P.rootDir)/bin/:$(PATH)

clean,64P ::
	-$(RM) package/lib/lib/videnc_copy/package/package_ti.sdo.ce.examples.codecs.videnc_copy.o64P
	-$(RM) package/lib/lib/videnc_copy/videnc_copy.o64P
	-$(RM) package/lib/lib/videnc_copy/package/package_ti.sdo.ce.examples.codecs.videnc_copy.s64P
	-$(RM) package/lib/lib/videnc_copy/videnc_copy.s64P

lib/videnc_copy.a64P: package/lib/lib/videnc_copy/package/package_ti.sdo.ce.examples.codecs.videnc_copy.o64P package/lib/lib/videnc_copy/videnc_copy.o64P lib/videnc_copy.a64P.mak

clean::
	-$(RM) lib/videnc_copy.a64P.mak