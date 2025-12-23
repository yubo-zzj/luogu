param(
    [string]$FilePath = ""
)

if ([string]::IsNullOrWhiteSpace($FilePath)) {
    $files = Get-ChildItem -Path . -Filter *.cpp | Sort-Object Name
    if ($files.Count -eq 0) {
        Write-Host "No .cpp files found in current directory." -ForegroundColor Red
        exit 1
    }
    $FilePath = $files[0].FullName
}

$gpp = "C:\msys64\mingw64\bin\g++.exe"
if (-not (Test-Path $gpp)) {
    Write-Host "g++ not found at $gpp. Please update the script or ensure MSYS2 is installed." -ForegroundColor Yellow
}

$exeName = [System.IO.Path]::GetFileNameWithoutExtension($FilePath) + ".exe"
$exePath = Join-Path -Path (Split-Path $FilePath -Parent) -ChildPath $exeName

Write-Host "Compiling:`n  $FilePath" -ForegroundColor Cyan
cmd /c "`"$gpp`" -g -std=c++17 `"$FilePath`" -o `"$exePath`""

if (-not (Test-Path $exePath)) {
    Write-Host "Build failed — executable not produced." -ForegroundColor Red
    exit 1
}

Write-Host "Running: $exePath" -ForegroundColor Green
cmd /c "`"$exePath`""

Write-Host "Exit code: $LASTEXITCODE"
Write-Host "Press any key to continue..."
[System.Console]::ReadKey() | Out-Null
