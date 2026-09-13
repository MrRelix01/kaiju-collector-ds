# Kaiju Collector DS

Kaiju Collector DS is a Nintendo DS homebrew project built with devkitPro (`devkitARM` + `libnds`).

Current default ROM behavior:
- Diagnostic boot test using only libnds console output.
- Lower-screen boot confirmation text and touch/button input feedback.
- Top-screen solid-color test with visible marker text.
- No NitroFS or external startup file dependency.

## Repository structure

- `/source` - active ARM9 entrypoint and modules
- `/source/prototype` - preserved battle prototype entrypoint
- `/include` - shared headers
- `/assets/graphics` - reserved graphics assets
- `/assets/audio` - reserved audio assets
- `/assets/maps` - reserved map assets
- `/data` - game data files and NitroFS-ready data
- `/generated` - generated asset outputs
- `/build` - local build output (ignored in git)
- `/docs` - architecture and design documentation
- `/.github/workflows` - CI build pipeline

## Local build (devkitPro)

1. Install devkitPro with Nintendo DS support (`devkitARM`, `libnds`).
2. Ensure `DEVKITPRO` and `DEVKITARM` environment variables are set.
3. Build:

```bash
make clean
make
```

Expected ROM output:

- `kaiju_collector_boot_test.nds`

## GitHub Actions build

The workflow at `.github/workflows/build-nds.yml` runs on:
- Pushes to `main`
- Pull requests

It compiles the ROM with the official `devkitpro/devkitarm` container and uploads artifact:
- Artifact name: `kaiju-collector-boot-test`
- Artifact file: `kaiju_collector_boot_test.nds`

## Downloading the built ROM artifact

After a workflow run completes:
1. Open the repository **Actions** tab.
2. Open the latest **Build Kaiju Collector DS ROM** run.
3. Download the **kaiju-collector-boot-test** artifact.
