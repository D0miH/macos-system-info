{
    "targets": [{
        "target_name": "smcnodekit",
        "sources": [
            "natives/SMCPPKit/SMCKit.cpp",
            "natives/SMCNodeKit.cpp",
            "natives/main.cpp"
        ],
        'include_dirs': [
            "src",
            "<!(node -e \"require('nan')\")"
        ],
        'cflags!': ['-fno-exceptions'],
        'cflags_cc!': ['-fno-exceptions'],
        'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'CLANG_CXX_LIBRARY': 'libc++',
            'MACOSX_DEPLOYMENT_TARGET': '10.7',
        },
        'msvs_settings': {
            'VCCLCompilerTool': {'ExceptionHandling': 1},
        },
        "conditions": [
            ['OS=="mac"', {
                'cflags+': ['-fvisibility=hidden'],
                'xcode_settings': {
                    'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES',  # -fvisibility=hidden
                }
            }]
        ]
    }]
}
