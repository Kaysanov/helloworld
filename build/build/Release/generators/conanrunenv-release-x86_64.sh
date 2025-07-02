script_folder="/home/sas/src/helloworld/build/build/Release/generators"
echo "echo Restoring environment" > "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
for v in PATH LD_LIBRARY_PATH DYLD_LIBRARY_PATH ALSA_CONFIG_DIR
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
    else
        echo unset $v >> "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
    fi
done


export PATH="/home/sas/.conan2/p/pulse479518f2e279d/p/bin:$PATH"
export LD_LIBRARY_PATH="/home/sas/.conan2/p/pulse479518f2e279d/p/lib:/home/sas/.conan2/p/pulse479518f2e279d/p/lib/pulseaudio:/home/sas/.conan2/p/libsnf7a6f70f3f936/p/lib:$LD_LIBRARY_PATH"
export DYLD_LIBRARY_PATH="/home/sas/.conan2/p/pulse479518f2e279d/p/lib:/home/sas/.conan2/p/pulse479518f2e279d/p/lib/pulseaudio:/home/sas/.conan2/p/libsnf7a6f70f3f936/p/lib:$DYLD_LIBRARY_PATH"
export ALSA_CONFIG_DIR="/home/sas/.conan2/p/libal3b7a099ce9ae0/p/res/alsa"