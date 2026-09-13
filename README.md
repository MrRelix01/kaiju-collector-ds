# Kaiju Collector DS

Kaiju Collector DS is a Nintendo DS homebrew prototype built with devkitPro (`devkitARM` + `libnds`).

Current prototype behavior:
- Title screen on boot using both DS screens.
- Start input via touchscreen (primary) or physical **A**.
- Battle prototype with `Pebblit` vs `Emberjaw`.
- Touch buttons: **ATTACK**, **SCAN**, **PACK**, **KAIJU**.
- **A** acts as confirm, **B** acts as back where appropriate.
- Basic combat loop with HP, enemy counterattack, defeat handling, and battle reset.

## Repository structure

- `/source` - ARM9 gameplay source modules
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

- `kaiju_collector_ds.nds`

## GitHub Actions build

The workflow at `.github/workflows/build-nds.yml` runs on:
- Pushes to `main`
- Pull requests

It compiles the ROM with the official `devkitpro/devkitarm` container and uploads artifact:
- Artifact name: `kaiju-collector-ds`
- Artifact file: `kaiju_collector_ds.nds`

## Downloading the built ROM artifact

After a workflow run completes:
1. Open the repository **Actions** tab.
2. Open the latest **Build Kaiju Collector DS ROM** run.
3. Download the **kaiju-collector-ds** artifact.
