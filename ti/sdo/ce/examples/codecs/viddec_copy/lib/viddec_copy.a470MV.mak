#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.MVArm9{1,0,3.4,3
#
ifneq (clean,$(MAKECMDGOALS))
-include package/lib/lib/viddec_copy/package/package_ti.sdo.ce.examples.codecs.viddec_copy.o470MV.dep
endif

package/lib/lib/viddec_copy/package/package_ti.sdo.ce.examples.codecs.viddec_copy.o470MV: | .interfaces
package/lib/lib/viddec_copy/package/package_ti.sdo.ce.examples.codecs.viddec_copy.o470MV: package/package_ti.sdo.ce.examples.codecs.viddec_copy.c lib/viddec_copy.a470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing   -Dfar=  -D__xdc_bld_pkg_c__=package.bld.c -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/viddec_copy/package/package_ti.sdo.ce.examples.codecs.viddec_copy.o470MV:LD_LIBRARY_PATH=

package/lib/lib/viddec_copy/package/package_ti.sdo.ce.examples.codecs.viddec_copy.s470MV: | .interfaces
package/lib/lib/viddec_copy/package/package_ti.sdo.ce.examples.codecs.viddec_copy.s470MV: package/package_ti.sdo.ce.examples.codecs.viddec_copy.c lib/viddec_copy.a470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV -S $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -Wall -fno-strict-aliasing   -Dfar=  -D__xdc_bld_pkg_c__=package.bld.c -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/viddec_copy/package/package_ti.sdo.ce.examples.codecs.viddec_copy.s470MV:LD_LIBRARY_PATH=

ifneq (clean,$(MAKECMDGOALS))
-include package/lib/lib/viddec_copy/viddec_copy.o470MV.dep
endif

package/lib/lib/viddec_copy/viddec_copy.o470MV: | .interfaces
package/lib/lib/viddec_copy/viddec_copy.o470MV: viddec_copy.c lib/viddec_copy.a470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing   -Dfar=  -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/viddec_copy/viddec_copy.o470MV:LD_LIBRARY_PATH=

package/lib/lib/viddec_copy/viddec_copy.s470MV: | .interfaces
package/lib/lib/viddec_copy/viddec_copy.s470MV: viddec_copy.c lib/viddec_copy.a470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV -S $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -Wall -fno-strict-aliasing   -Dfar=  -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/viddec_copy/viddec_copy.s470MV:LD_LIBRARY_PATH=

clean,470MV ::
	-$(RM) package/lib/lib/viddec_copy/package/package_ti.sdo.ce.examples.codecs.viddec_copy.o470MV
	-$(RM) package/lib/lib/viddec_copy/viddec_copy.o470MV
	-$(RM) package/lib/lib/viddec_copy/package/package_ti.sdo.ce.examples.codecs.viddec_copy.s470MV
	-$(RM) package/lib/lib/viddec_copy/viddec_copy.s470MV

lib/viddec_copy.a470MV: package/lib/lib/viddec_copy/package/package_ti.sdo.ce.examples.codecs.viddec_copy.o470MV package/lib/lib/viddec_copy/viddec_copy.o470MV lib/viddec_copy.a470MV.mak

clean::
	-$(RM) lib/viddec_copy.a470MV.mak