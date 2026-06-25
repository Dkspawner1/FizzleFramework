dxc -T vs_6_0 -E main -spirv -fvk-use-dx-layout `
    -Fo assets/shaders/compiled/spirv/quad.vert.spv `
    assets/shaders/src/quad.vert.hlsl

dxc -T ps_6_0 -E main -spirv -fvk-use-dx-layout `
    -Fo assets/shaders/compiled/spirv/quad.frag.spv `
    assets/shaders/src/quad.frag.hlsl