# invoke SourceDir generated makefile for rfWsnNode.pem3
rfWsnNode.pem3: .libraries,rfWsnNode.pem3
.libraries,rfWsnNode.pem3: package/cfg/rfWsnNode_pem3.xdl
	$(MAKE) -f C:\Users\antsis\workspace_v6_1\rfWsnNode_CC1310DK_7XD_TI_CC1310F128/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\antsis\workspace_v6_1\rfWsnNode_CC1310DK_7XD_TI_CC1310F128/src/makefile.libs clean

