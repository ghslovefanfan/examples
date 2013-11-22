#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.MVArm9{1,0,3.4,3
#
ifneq (clean,$(MAKECMDGOALS))
-include package/lib/lib/scale/scale.o470MV.dep
endif

package/lib/lib/scale/scale.o470MV: | .interfaces
package/lib/lib/scale/scale.o470MV: scale.c lib/scale.a470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing   -Dfar=  -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/scale/scale.o470MV:LD_LIBRARY_PATH=

package/lib/lib/scale/scale.s470MV: | .interfaces
package/lib/lib/scale/scale.s470MV: scale.c lib/scale.a470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV -S $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -Wall -fno-strict-aliasing   -Dfar=  -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/scale/scale.s470MV:LD_LIBRARY_PATH=

ifneq (clean,$(MAKECMDGOALS))
-include package/lib/lib/scale/package/package_ti.sdo.ce.examples.extensions.scale.o470MV.dep
endif

package/lib/lib/scale/package/package_ti.sdo.ce.examples.extensions.scale.o470MV: | .interfaces
package/lib/lib/scale/package/package_ti.sdo.ce.examples.extensions.scale.o470MV: package/package_ti.sdo.ce.examples.extensions.scale.c lib/scale.a470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing   -Dfar=  -D__xdc_bld_pkg_c__=package.bld.c -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/scale/package/package_ti.sdo.ce.examples.extensions.scale.o470MV:LD_LIBRARY_PATH=

package/lib/lib/scale/package/package_ti.sdo.ce.examples.extensions.scale.s470MV: | .interfaces
package/lib/lib/scale/package/package_ti.sdo.ce.examples.extensions.scale.s470MV: package/package_ti.sdo.ce.examples.extensions.scale.c lib/scale.a470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV -S $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -Wall -fno-strict-aliasing   -Dfar=  -D__xdc_bld_pkg_c__=package.bld.c -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/scale/package/package_ti.sdo.ce.examples.extensions.scale.s470MV:LD_LIBRARY_PATH=

ifneq (clean,$(MAKECMDGOALS))
-include package/lib/lib/scale/scale_skel.o470MV.dep
endif

package/lib/lib/scale/scale_skel.o470MV: | .interfaces
package/lib/lib/scale/scale_skel.o470MV: scale_skel.c lib/scale.a470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing   -Dfar=  -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/scale/scale_skel.o470MV:LD_LIBRARY_PATH=

package/lib/lib/scale/scale_skel.s470MV: | .interfaces
package/lib/lib/scale/scale_skel.s470MV: scale_skel.c lib/scale.a470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV -S $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -Wall -fno-strict-aliasing   -Dfar=  -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/scale/scale_skel.s470MV:LD_LIBRARY_PATH=

ifneq (clean,$(MAKECMDGOALS))
-include package/lib/lib/scale/scale_stubs.o470MV.dep
endif

package/lib/lib/scale/scale_stubs.o470MV: | .interfaces
package/lib/lib/scale/scale_stubs.o470MV: scale_stubs.c lib/scale.a470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -Wall -fno-strict-aliasing   -Dfar=  -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/scale/scale_stubs.o470MV:LD_LIBRARY_PATH=

package/lib/lib/scale/scale_stubs.s470MV: | .interfaces
package/lib/lib/scale/scale_stubs.s470MV: scale_stubs.c lib/scale.a470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV -S $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -Wall -fno-strict-aliasing   -Dfar=  -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/lib/lib/scale/scale_stubs.s470MV:LD_LIBRARY_PATH=

clean,470MV ::
	-$(RM) package/lib/lib/scale/scale.o470MV
	-$(RM) package/lib/lib/scale/package/package_ti.sdo.ce.examples.extensions.scale.o470MV
	-$(RM) package/lib/lib/scale/scale_skel.o470MV
	-$(RM) package/lib/lib/scale/scale_stubs.o470MV
	-$(RM) package/lib/lib/scale/scale.s470MV
	-$(RM) package/lib/lib/scale/package/package_ti.sdo.ce.examples.extensions.scale.s470MV
	-$(RM) package/lib/lib/scale/scale_skel.s470MV
	-$(RM) package/lib/lib/scale/scale_stubs.s470MV

lib/scale.a470MV: package/lib/lib/scale/scale.o470MV package/lib/lib/scale/package/package_ti.sdo.ce.examples.extensions.scale.o470MV package/lib/lib/scale/scale_skel.o470MV package/lib/lib/scale/scale_stubs.o470MV lib/scale.a470MV.mak

clean::
	-$(RM) lib/scale.a470MV.mak
