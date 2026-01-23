# 🏁 PROJECT OVR//DRV

**OVR-DRV** (pronounced _OVERDRIVE_) is a stylized high-speed racing experience built in **Unreal Engine 5.6**, exploring the intersection of speed, control, and pure mechanical rhythm.

---

## 🚧 Project Overview

| Category      | Description       |
| ------------- | ----------------- |
| Engine        | Unreal Engine 5.6 |
| Language      | C++ & Blueprints  |
| Platform      | PC and consoles   |
| Current Phase | Pre-Production    |

---

## 🧩 Code & Asset Conventions

**Prefix:** `OD_`  
All in-game assets and code use the `OD` prefix to maintain consistent project identity.

**Examples:**

- Classes → `ODBaseVehicle`, `ODDriftComponent`
- Blueprints → `BP_OD_SportsCar`, `WBP_OD_HUD`
- Assets → `M_OD_CarPaint`, `NS_OD_DriftSmoke`

---

## 🗂️ Folder Structure

* /Source/OVRDRV/
* ├── Core/
* ├── Vehicles/
* ├── Systems/
* ├── Tracks/
* └── Interfaces/
* 
* /Content/OD/
* ├── Blueprints/
* ├── Materials/
* ├── Meshes/
* ├── Sounds/
* ├── FX/
* └── Data/

### Example Structure Usage
* PROJECT-OVR-DRV/
* ├── OVRDRV.uproject
* │
* ├── Source/
* │   └── OVRDRV/
* │       ├── Core/
* │       │   ├── ODGameMode.h/.cpp
* │       │   ├── ODGameInstance.h/.cpp
* │       │   ├── ODPlayerController.h/.cpp
* │       │   └── ODPlayerState.h/.cpp
* │       │
* │       ├── Vehicles/
* │       │   ├── Base/
* │       │   │   ├── ODBaseVehicle.h/.cpp
* │       │   │   └── ODVehicleData.h/.cpp
* │       │   │
* │       │   ├── Components/
* │       │   │   ├── ODDriftComponent.h/.cpp
* │       │   │   ├── ODBoostComponent.h/.cpp
* │       │   │   └── ODSuspensionComponent.h/.cpp
* │       │   │
* │       │   ├── Sports/ODSportsCar.h/.cpp
* │       │   └── Offroad/ODOffroadVehicle.h/.cpp
* │       │
* │       ├── Systems/
* │       │   ├── ODInputConfig.h/.cpp
* │       │   ├── ODSaveSystem.h/.cpp
* │       │   └── ODPhysicsHelper.h/.cpp
* │       │
* │       ├── Tracks/
* │       │   ├── ODTrackManager.h/.cpp
* │       │   └── ODCheckpoint.h/.cpp
* │       │
* │       └── Interfaces/
* │           ├── IDriveable.h
* │           ├── IDriftable.h
* │           └── IBoostable.h
* │
* ├── Content/OD/
* │   ├── Blueprints/
* │   │   ├── Vehicles/
* │   │   │   ├── BP_OD_SportsCar
* │   │   │   ├── BP_OD_OffroadVehicle
* │   │   │   └── BP_OD_BaseVehicle
* │   │   │
* │   │   ├── Components/
* │   │   │   ├── BP_OD_DriftComponent
* │   │   │   └── BP_OD_BoostComponent
* │   │   │
* │   │   ├── Tracks/
* │   │   │   ├── BP_OD_Track01
* │   │   │   └── BP_OD_Checkpoint
* │   │   │
* │   │   └── UI/
* │   │       ├── WBP_OD_HUD
* │   │       └── WBP_OD_MainMenu
* │   │
* │   ├── Materials/
* │   │   ├── M_OD_CarPaint
* │   │   ├── M_OD_Asphalt
* │   │   └── M_OD_Lights
* │   │
* │   ├── Meshes/
* │   │   ├── SM_OD_SportsCar
* │   │   ├── SM_OD_OffroadVehicle
* │   │   └── SM_OD_Barrier
* │   │
* │   ├── Textures/
* │   │   ├── T_OD_CarBody
* │   │   ├── T_OD_Tire
* │   │   └── T_OD_Track01
* │   │
* │   ├── Sounds/
* │   │   ├── S_OD_EngineLoop
* │   │   ├── S_OD_Boost
* │   │   └── S_OD_DriftScreech
* │   │
* │   ├── FX/
* │   │   ├── NS_OD_DriftSmoke
* │   │   └── NS_OD_NitroFlame
* │   │
* │   └── Data/
* │       ├── DT_OD_VehicleStats
* │       ├── DT_OD_TrackData
* │       └── Curve_OD_DriftGrip
* │
* ├── Config/
* │   ├── DefaultEngine.ini
* │   ├── DefaultGame.ini
* │   └── DefaultInput.ini
* │
* ├── Docs/
* │   ├── GDD/
* │   │   ├── PROJECT_OVRDRV_GDD.md
* │   │   └── VehicleSpecs.md
* │   ├── Branding/
* │   │   └── Logo_OVRDRV.png
* │   └── DevLogs/
* │       └── DevLog_001_Setup.md
* │
* ├── .gitignore
* ├── README.md
* └── LICENSE
* 

### Source

# 🗂️ Git Branching Guide – PROJECT OVR-DRV

---

## 💾 Version Control

The project uses **Git + Git LFS**.  
Recommended `.gitignore`: [Unreal Engine Standard Ignore](https://github.com/github/gitignore/blob/main/UnrealEngine.gitignore)

Main Branches:

- `main` — stable release
- `dev` — active development
- `feature/*` — individual features (e.g. `feature/drift-system`)

## 🌳 Branch Structure

| Branch Name | Purpose                                  |
| ----------- | ---------------------------------------- |
| `main`      | ✅ Production-ready, stable builds only  |
| `dev`       | 🧪 Active development integration branch |
| `feature/*` | 🔧 New features or systems               |
| `hotfix/*`  | 🛠️ Emergency bugfixes (optional)         |

---

| Type         | Example                   |
| ------------ | ------------------------- |
| Features     | `feature/vehicle-spawner` |
| Bugfixes     | `feature/fix-speed-curve` |
| Hotfixes     | `hotfix/input-bug`        |
| Experimental | `feature/test-new-fx`     |

---

## 📘 Documentation

Located in `/Docs/`:

- `GDD/PROJECT_OVRDRV_GDD.md`
- `DevLogs/`
- `Branding/`

---

## 🔧 Setup

1. Clone repository
2. Run `Setup.bat` and `GenerateProjectFiles.bat`
3. Open `OVRDRV.uproject`
4. Build and launch in Unreal Engine 5.6

---

## 🧠 Credits

**Game Design / Development:** [KLAUS 117] / [AYOBAMI OYESIKU]
**Engine:** Unreal Engine 5.6  
**Status:** In Development

---

> _PROJECT OVR-DRV // A study in motion, precision, and control._
