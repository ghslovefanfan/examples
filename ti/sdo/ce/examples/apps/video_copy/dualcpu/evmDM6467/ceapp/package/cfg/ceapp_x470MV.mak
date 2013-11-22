#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.MVArm9{1,0,3.4,3
#
ifneq (clean,$(MAKECMDGOALS))
-include package/cfg/ceapp_x470MV.o470MV.dep
endif

package/cfg/ceapp_x470MV.o470MV: | .interfaces
package/cfg/ceapp_x470MV.o470MV: package/cfg/ceapp_x470MV.c package/cfg/ceapp_x470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused  -Dfar=   -Dxdc_cfg__header__='ceapp/package/cfg/ceapp_x470MV.h'  -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/cfg/ceapp_x470MV.o470MV:LD_LIBRARY_PATH=

package/cfg/ceapp_x470MV.s470MV: | .interfaces
package/cfg/ceapp_x470MV.s470MV: package/cfg/ceapp_x470MV.c package/cfg/ceapp_x470MV.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) cl470MV -S $< ...
	$(gnu.targets.MVArm9.rootDir)/bin/arm_v5t_le-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused  -Dfar=   -Dxdc_cfg__header__='ceapp/package/cfg/ceapp_x470MV.h'  -Dxdc_target_name__=MVArm9 -Dxdc_target_types__=gnu/targets/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_3_4_3 -O2  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/cfg/ceapp_x470MV.s470MV:LD_LIBRARY_PATH=

clean,470MV ::
	-$(RM) package/cfg/ceapp_x470MV.o470MV
	-$(RM) package/cfg/ceapp_x470MV.s470MV

ceapp.x470MV: package/cfg/ceapp_x470MV.o470MV package/cfg/ceapp_x470MV.mak

clean::
	-$(RM) package/cfg/ceapp_x470MV.mak
