#
# Copyright (c) Citrix Systems, Inc.
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
#   1) Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
# 
#   2) Redistributions in binary form must reproduce the above
#      copyright notice, this list of conditions and the following
#      disclaimer in the documentation and/or other materials
#      provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.
#

#
# Please do not customize this script; your changes will be lost on upgrade.
#
# Instead, create and customize the file XenServerProfile.ps1.
# Put it in $env:windir\system32\WindowsPowerShell\v1.0 for system-wide# configuration, or $env:UserProfile\Documents\WindowsPowerShell# for per-user configuration.
#

if (Get-Variable XenServer_Environment_Initialized -ValueOnly -ErrorAction SilentlyContinue)
{
    return
}

$systemWidePath = "$env:windir\system32\WindowsPowerShell\v1.0"
$perUserPath = "$env:UserProfile\Documents\WindowsPowerShell"

if (Test-Path "$systemWidePath\XenServerProfile.ps1")
{
    . "$systemWidePath\XenServerProfile.ps1"
}

if (Test-Path "$perUserPath\XenServerProfile.ps1")
{
    . "$perUserPath\XenServerProfile.ps1"
}

Remove-Item variable:systemWidePath
Remove-Item variable:perUserPath

$XenServer_Environment_Initialized = $true
