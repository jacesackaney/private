#include <algorithm>
#include <array>
#include <fstream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <ShlObj.h>
#include <Windows.h>
#endif

#include "imgui/imgui.h"
#include "imgui/imgui_stdlib.h"

#include "imguiCustom.h"

#include "GUI.h"
#include "imgui/imgui.h"
#include "Config.h"
#include "ConfigStructs.h"
#include "Hacks/Misc.h"
#include "InventoryChanger/InventoryChanger.h"
#include "Helpers.h"
#include "Interfaces.h"

#include "SDK/InputSystem.h"
#include "Hacks/Visuals.h"

#include "Hacks/AntiAim.h"
#include "Hacks/Backtrack.h"
#include "Hacks/Sound.h"
#include "Hacks/StreamProofESP.h"
#include "Hooks.h"
#include "stb_image.h"

#include "InventoryChanger/StaticData.h"
#include "InventoryChanger/Inventory.h"
#include <charconv>
#include <chrono>
#include <cstdint>
#include <string_view>
#include <type_traits>
#include <utility>

#define STBI_ONLY_PNG
#define STBI_NO_FAILURE_STRINGS
#define STBI_NO_STDIO
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui_internal.h"
#include "../imgui/imgui_stdlib.h"
#include "../Interfaces.h"
#include "inventorychanger/InventoryChanger.h"
#include "../ProtobufReader.h"
#include "../Texture.h"

#include "../nlohmann/json.hpp"

#include "../SDK/ClassId.h"
#include "../SDK/Client.h"
#include "../SDK/ClientClass.h"
#include "../SDK/ConVar.h"
#include "../SDK/Cvar.h"
#include "../SDK/EconItemView.h"
#include "../SDK/Entity.h"
#include "../SDK/EntityList.h"
#include "../SDK/FileSystem.h"
#include "../SDK/FrameStage.h"
#include "../SDK/GameEvent.h"
#include "../SDK/GlobalVars.h"
#include "../SDK/ItemSchema.h"
#include "../SDK/LocalPlayer.h"
#include "../SDK/ModelInfo.h"
#include "../SDK/PlayerResource.h"
#include "../SDK/Platform.h"
#include "../SDK/WeaponId.h"
#include "inventorychanger/ToolUser.h"


#include "../Helpers.h"




#include "../nlohmann/json.hpp"
#include "../imgui/imgui.h"

#include "../ConfigStructs.h"
#include "../InputUtil.h"
#include "hacks/Glow.h"
#include "../Helpers.h"
#include "../Interfaces.h"
#include "../Memory.h"
#include "../SDK/ClassId.h"
#include "../SDK/ClientClass.h"
#include "../SDK/Engine.h"
#include "../SDK/Entity.h"
#include "../SDK/EntityList.h"
#include "../SDK/GlowObjectManager.h"

#include "../SDK/Utils.h"
#include "../SDK/UtlVector.h"
#include "../SDK/Vector.h"
#include "../imguiCustom.h"
#include <algorithm>
#include <array>
#include <iomanip>
#include <mutex>
#include <numbers>
#include <numeric>
#include <sstream>
#include <vector>

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui_internal.h"
#include "../imgui/imgui_stdlib.h"

#include "../ConfigStructs.h"
#include "../InputUtil.h"
#include "../Interfaces.h"
#include "../Memory.h"
#include "../ProtobufReader.h"

#include "hacks/EnginePrediction.h"
#include "hacks/Misc.h"

#include "../SDK/ClassId.h"
#include "../SDK/Client.h"
#include "../SDK/ClientClass.h"
#include "../SDK/ClientMode.h"
#include "../SDK/ConVar.h"
#include "../SDK/Cvar.h"
#include "../SDK/Engine.h"
#include "../SDK/EngineTrace.h"
#include "../SDK/Entity.h"
#include "../SDK/EntityList.h"
#include "../SDK/FrameStage.h"
#include "../SDK/GameEvent.h"
#include "../SDK/GlobalVars.h"
#include "../SDK/ItemSchema.h"
#include "../SDK/Localize.h"
#include "../SDK/LocalPlayer.h"
#include "../SDK/NetworkChannel.h"
#include "../SDK/Panorama.h"
#include "../SDK/Platform.h"
#include "../SDK/UserCmd.h"
#include "../SDK/UtlVector.h"
#include "../SDK/Vector.h"
#include "../SDK/WeaponData.h"
#include "../SDK/WeaponId.h"
#include "../SDK/WeaponSystem.h"

#include "../GUI.h"
#include "../Helpers.h"
#include "../Hooks.h"
#include "../GameData.h"

#include "../imguiCustom.h"

#include <algorithm>
#include <array>
#include <forward_list>
#include <limits>
#include <numbers>
#include <unordered_map>
#include <vector>

#include "hacks/StreamProofESP.h"

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui_internal.h"

#include "../Config.h"
#include "../GameData.h"
#include "../Helpers.h"
#include "../InputUtil.h"
#include "../SDK/Engine.h"
#include "../SDK/GlobalVars.h"
#include "../Memory.h"

#include "../imguiCustom.h"
#include <array>
#include <cstring>
#include <string_view>
#include <utility>
#include <vector>

#include "../imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../imgui/imgui_internal.h"

#include "../ConfigStructs.h"
#include "../fnv.h"
#include "../GameData.h"
#include "../Helpers.h"
#include "../Interfaces.h"
#include "../Memory.h"
#include "../imguiCustom.h"
#include "Hacks/Visuals.h"

#include "../SDK/ConVar.h"
#include "../SDK/Cvar.h"
#include "../SDK/Engine.h"
#include "../SDK/Entity.h"
#include "../SDK/EntityList.h"
#include "../SDK/FrameStage.h"
#include "../SDK/GameEvent.h"
#include "../SDK/GlobalVars.h"
#include "../SDK/Input.h"
#include "../SDK/LocalPlayer.h"
#include "../SDK/Material.h"
#include "../SDK/MaterialSystem.h"
#include "../SDK/ViewRenderBeams.h"




struct BulletTracers : ColorToggle {
    BulletTracers() : ColorToggle{ 0.0f, 0.75f, 1.0f, 1.0f } {}
};

struct VisualsConfig {
    bool disablePostProcessing{ false };
    bool inverseRagdollGravity{ false };
    bool noFog{ false };
    bool no3dSky{ false };
    bool noAimPunch{ false };
    bool noViewPunch{ false };
    bool noHands{ false };
    bool noSleeves{ false };
    bool noWeapons{ false };
    bool noSmoke{ false };
    bool noBlur{ false };
    bool noScopeOverlay{ false };
    bool noGrass{ false };
    bool noShadows{ false };
    bool wireframeSmoke{ false };
    bool zoom{ false };
    KeyBindToggle zoomKey;
    bool thirdperson{ false };
    KeyBindToggle thirdpersonKey;
    int thirdpersonDistance{ 0 };
    int viewmodelFov{ 0 };
    int fov{ 0 };
    int farZ{ 0 };
    int flashReduction{ 0 };
    float brightness{ 0.0f };
    int skybox{ 0 };
    ColorToggle3 world;
    ColorToggle3 sky;
    bool deagleSpinner{ false };
    int screenEffect{ 0 };
    int hitEffect{ 0 };
    float hitEffectTime{ 0.6f };
    int hitMarker{ 0 };
    float hitMarkerTime{ 0.6f };
    BulletTracers bulletTracers;
    ColorToggle molotovHull{ 1.0f, 0.27f, 0.0f, 0.3f };

    struct ColorCorrection {
        bool enabled = false;
        float blue = 0.0f;
        float red = 0.0f;
        float mono = 0.0f;
        float saturation = 0.0f;
        float ghost = 0.0f;
        float green = 0.0f;
        float yellow = 0.0f;
    } colorCorrection;
} visualsConfig;


static void from_json(const json& j, VisualsConfig::ColorCorrection& c)
{
    read(j, "Enabled", c.enabled);
    read(j, "Blue", c.blue);
    read(j, "Red", c.red);
    read(j, "Mono", c.mono);
    read(j, "Saturation", c.saturation);
    read(j, "Ghost", c.ghost);
    read(j, "Green", c.green);
    read(j, "Yellow", c.yellow);
}

static void from_json(const json& j, BulletTracers& o)
{
    from_json(j, static_cast<ColorToggle&>(o));
}

static void from_json(const json& j, VisualsConfig& v)
{
    read(j, "Disable post-processing", v.disablePostProcessing);
    read(j, "Inverse ragdoll gravity", v.inverseRagdollGravity);
    read(j, "No fog", v.noFog);
    read(j, "No 3d sky", v.no3dSky);
    read(j, "No aim punch", v.noAimPunch);
    read(j, "No view punch", v.noViewPunch);
    read(j, "No hands", v.noHands);
    read(j, "No sleeves", v.noSleeves);
    read(j, "No weapons", v.noWeapons);
    read(j, "No smoke", v.noSmoke);
    read(j, "No blur", v.noBlur);
    read(j, "No scope overlay", v.noScopeOverlay);
    read(j, "No grass", v.noGrass);
    read(j, "No shadows", v.noShadows);
    read(j, "Wireframe smoke", v.wireframeSmoke);
    read(j, "Zoom", v.zoom);
    read(j, "Zoom key", v.zoomKey);
    read(j, "Thirdperson", v.thirdperson);
    read(j, "Thirdperson key", v.thirdpersonKey);
    read(j, "Thirdperson distance", v.thirdpersonDistance);
    read(j, "Viewmodel FOV", v.viewmodelFov);
    read(j, "FOV", v.fov);
    read(j, "Far Z", v.farZ);
    read(j, "Flash reduction", v.flashReduction);
    read(j, "Brightness", v.brightness);
    read(j, "Skybox", v.skybox);
    read<value_t::object>(j, "World", v.world);
    read<value_t::object>(j, "Sky", v.sky);
    read(j, "Deagle spinner", v.deagleSpinner);
    read(j, "Screen effect", v.screenEffect);
    read(j, "Hit effect", v.hitEffect);
    read(j, "Hit effect time", v.hitEffectTime);
    read(j, "Hit marker", v.hitMarker);
    read(j, "Hit marker time", v.hitMarkerTime);
    read<value_t::object>(j, "Color correction", v.colorCorrection);
    read<value_t::object>(j, "Bullet Tracers", v.bulletTracers);
    read<value_t::object>(j, "Molotov Hull", v.molotovHull);
}

static void to_json(json& j, const VisualsConfig::ColorCorrection& o, const VisualsConfig::ColorCorrection& dummy)
{
    WRITE("Enabled", enabled);
    WRITE("Blue", blue);
    WRITE("Red", red);
    WRITE("Mono", mono);
    WRITE("Saturation", saturation);
    WRITE("Ghost", ghost);
    WRITE("Green", green);
    WRITE("Yellow", yellow);
}

static void to_json(json& j, const BulletTracers& o, const BulletTracers& dummy = {})
{
    to_json(j, static_cast<const ColorToggle&>(o), dummy);
}

static void to_json(json& j, const VisualsConfig& o)
{
    const VisualsConfig dummy;

    WRITE("Disable post-processing", disablePostProcessing);
    WRITE("Inverse ragdoll gravity", inverseRagdollGravity);
    WRITE("No fog", noFog);
    WRITE("No 3d sky", no3dSky);
    WRITE("No aim punch", noAimPunch);
    WRITE("No view punch", noViewPunch);
    WRITE("No hands", noHands);
    WRITE("No sleeves", noSleeves);
    WRITE("No weapons", noWeapons);
    WRITE("No smoke", noSmoke);
    WRITE("No blur", noBlur);
    WRITE("No scope overlay", noScopeOverlay);
    WRITE("No grass", noGrass);
    WRITE("No shadows", noShadows);
    WRITE("Wireframe smoke", wireframeSmoke);
    WRITE("Zoom", zoom);
    WRITE("Zoom key", zoomKey);
    WRITE("Thirdperson", thirdperson);
    WRITE("Thirdperson key", thirdpersonKey);
    WRITE("Thirdperson distance", thirdpersonDistance);
    WRITE("Viewmodel FOV", viewmodelFov);
    WRITE("FOV", fov);
    WRITE("Far Z", farZ);
    WRITE("Flash reduction", flashReduction);
    WRITE("Brightness", brightness);
    WRITE("Skybox", skybox);
    WRITE("World", world);
    WRITE("Sky", sky);
    WRITE("Deagle spinner", deagleSpinner);
    WRITE("Screen effect", screenEffect);
    WRITE("Hit effect", hitEffect);
    WRITE("Hit effect time", hitEffectTime);
    WRITE("Hit marker", hitMarker);
    WRITE("Hit marker time", hitMarkerTime);
    WRITE("Color correction", colorCorrection);
    WRITE("Bullet Tracers", bulletTracers);
    WRITE("Molotov Hull", molotovHull);
}

bool Visuals::isThirdpersonOn() noexcept
{
    return visualsConfig.thirdperson;
}

bool Visuals::isZoomOn() noexcept
{
    return visualsConfig.zoom;
}

bool Visuals::isSmokeWireframe() noexcept
{
    return visualsConfig.wireframeSmoke;
}

bool Visuals::isDeagleSpinnerOn() noexcept
{
    return visualsConfig.deagleSpinner;
}

bool Visuals::shouldRemoveFog() noexcept
{
    return visualsConfig.noFog;
}

bool Visuals::shouldRemoveScopeOverlay() noexcept
{
    return visualsConfig.noScopeOverlay;
}

bool Visuals::shouldRemoveSmoke() noexcept
{
    return visualsConfig.noSmoke;
}

float Visuals::viewModelFov() noexcept
{
    return static_cast<float>(visualsConfig.viewmodelFov);
}

float Visuals::fov() noexcept
{
    return static_cast<float>(visualsConfig.fov);
}

float Visuals::farZ() noexcept
{
    return static_cast<float>(visualsConfig.farZ);
}

void Visuals::performColorCorrection() noexcept
{
    if (const auto& cfg = visualsConfig.colorCorrection; cfg.enabled) {
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + WIN32_LINUX(0x49C, 0x908)) = cfg.blue;
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + WIN32_LINUX(0x4A4, 0x918)) = cfg.red;
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + WIN32_LINUX(0x4AC, 0x928)) = cfg.mono;
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + WIN32_LINUX(0x4B4, 0x938)) = cfg.saturation;
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + WIN32_LINUX(0x4C4, 0x958)) = cfg.ghost;
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + WIN32_LINUX(0x4CC, 0x968)) = cfg.green;
        *reinterpret_cast<float*>(std::uintptr_t(memory->clientMode) + WIN32_LINUX(0x4D4, 0x978)) = cfg.yellow;
    }
}

void Visuals::inverseRagdollGravity() noexcept
{
    static auto ragdollGravity = interfaces->cvar->findVar("cl_ragdoll_gravity");
    ragdollGravity->setValue(visualsConfig.inverseRagdollGravity ? -600 : 600);
}

void Visuals::colorWorld() noexcept
{
    if (!visualsConfig.world.enabled && !visualsConfig.sky.enabled)
        return;

    for (short h = interfaces->materialSystem->firstMaterial(); h != interfaces->materialSystem->invalidMaterial(); h = interfaces->materialSystem->nextMaterial(h)) {
        const auto mat = interfaces->materialSystem->getMaterial(h);

        if (!mat || !mat->isPrecached())
            continue;

        const std::string_view textureGroup = mat->getTextureGroupName();

        if (visualsConfig.world.enabled && (textureGroup.starts_with("World") || textureGroup.starts_with("StaticProp"))) {
            if (visualsConfig.world.asColor3().rainbow)
                mat->colorModulate(rainbowColor(visualsConfig.world.asColor3().rainbowSpeed));
            else
                mat->colorModulate(visualsConfig.world.asColor3().color);
        }
        else if (visualsConfig.sky.enabled && textureGroup.starts_with("SkyBox")) {
            if (visualsConfig.sky.asColor3().rainbow)
                mat->colorModulate(rainbowColor(visualsConfig.sky.asColor3().rainbowSpeed));
            else
                mat->colorModulate(visualsConfig.sky.asColor3().color);
        }
    }
}

void Visuals::modifySmoke(FrameStage stage) noexcept
{
    if (stage != FrameStage::RENDER_START && stage != FrameStage::RENDER_END)
        return;

    constexpr std::array smokeMaterials{
        "particle/vistasmokev1/vistasmokev1_emods",
        "particle/vistasmokev1/vistasmokev1_emods_impactdust",
        "particle/vistasmokev1/vistasmokev1_fire",
        "particle/vistasmokev1/vistasmokev1_smokegrenade"
    };

    for (const auto mat : smokeMaterials) {
        const auto material = interfaces->materialSystem->findMaterial(mat);
        material->setMaterialVarFlag(MaterialVarFlag::NO_DRAW, stage == FrameStage::RENDER_START && visualsConfig.noSmoke);
        material->setMaterialVarFlag(MaterialVarFlag::WIREFRAME, stage == FrameStage::RENDER_START && visualsConfig.wireframeSmoke);
    }
}

void Visuals::thirdperson() noexcept
{
    if (!visualsConfig.thirdperson)
        return;

    memory->input->isCameraInThirdPerson = (!visualsConfig.thirdpersonKey.isSet() || visualsConfig.thirdpersonKey.isToggled()) && localPlayer && localPlayer->isAlive();
    memory->input->cameraOffset.z = static_cast<float>(visualsConfig.thirdpersonDistance);
}

void Visuals::removeVisualRecoil(FrameStage stage) noexcept
{
    if (!localPlayer || !localPlayer->isAlive())
        return;

    static Vector aimPunch;
    static Vector viewPunch;

    if (stage == FrameStage::RENDER_START) {
        aimPunch = localPlayer->aimPunchAngle();
        viewPunch = localPlayer->viewPunchAngle();

        if (visualsConfig.noAimPunch)
            localPlayer->aimPunchAngle() = Vector{ };

        if (visualsConfig.noViewPunch)
            localPlayer->viewPunchAngle() = Vector{ };

    }
    else if (stage == FrameStage::RENDER_END) {
        localPlayer->aimPunchAngle() = aimPunch;
        localPlayer->viewPunchAngle() = viewPunch;
    }
}

void Visuals::removeBlur(FrameStage stage) noexcept
{
    if (stage != FrameStage::RENDER_START && stage != FrameStage::RENDER_END)
        return;

    static auto blur = interfaces->materialSystem->findMaterial("dev/scope_bluroverlay");
    blur->setMaterialVarFlag(MaterialVarFlag::NO_DRAW, stage == FrameStage::RENDER_START && visualsConfig.noBlur);
}

void Visuals::updateBrightness() noexcept
{
    static auto brightness = interfaces->cvar->findVar("mat_force_tonemap_scale");
    brightness->setValue(visualsConfig.brightness);
}

void Visuals::removeGrass(FrameStage stage) noexcept
{
    if (stage != FrameStage::RENDER_START && stage != FrameStage::RENDER_END)
        return;

    constexpr auto getGrassMaterialName = []() noexcept -> const char* {
        switch (fnv::hashRuntime(interfaces->engine->getLevelName())) {
        case fnv::hash("dz_blacksite"): return "detail/detailsprites_survival";
        case fnv::hash("dz_sirocco"): return "detail/dust_massive_detail_sprites";
        case fnv::hash("coop_autumn"): return "detail/autumn_detail_sprites";
        case fnv::hash("dz_frostbite"): return "ski/detail/detailsprites_overgrown_ski";
            // dz_junglety has been removed in 7/23/2020 patch
            // case fnv::hash("dz_junglety"): return "detail/tropical_grass";
        default: return nullptr;
        }
    };

    if (const auto grassMaterialName = getGrassMaterialName())
        interfaces->materialSystem->findMaterial(grassMaterialName)->setMaterialVarFlag(MaterialVarFlag::NO_DRAW, stage == FrameStage::RENDER_START && visualsConfig.noGrass);
}

void Visuals::remove3dSky() noexcept
{
    static auto sky = interfaces->cvar->findVar("r_3dsky");
    sky->setValue(!visualsConfig.no3dSky);
}

void Visuals::removeShadows() noexcept
{
    static auto shadows = interfaces->cvar->findVar("cl_csm_enabled");
    shadows->setValue(!visualsConfig.noShadows);
}

void Visuals::applyZoom(FrameStage stage) noexcept
{
    if (visualsConfig.zoom && localPlayer) {
        if (stage == FrameStage::RENDER_START && (localPlayer->fov() == 90 || localPlayer->fovStart() == 90)) {
            if (visualsConfig.zoomKey.isToggled()) {
                localPlayer->fov() = 40;
                localPlayer->fovStart() = 40;
            }
        }
    }
}

#ifdef _WIN32
#undef xor
#define DRAW_SCREEN_EFFECT(material) \
{ \
    const auto drawFunction = memory->drawScreenEffectMaterial; \
    int w, h; \
    interfaces->engine->getScreenSize(w, h); \
    __asm { \
        __asm push h \
        __asm push w \
        __asm push 0 \
        __asm xor edx, edx \
        __asm mov ecx, material \
        __asm call drawFunction \
        __asm add esp, 12 \
    } \
}

#else
#define DRAW_SCREEN_EFFECT(material) \
{ \
    int w, h; \
    interfaces->engine->getScreenSize(w, h); \
    reinterpret_cast<void(*)(Material*, int, int, int, int)>(memory->drawScreenEffectMaterial)(material, 0, 0, w, h); \
}
#endif

void Visuals::applyScreenEffects() noexcept
{
    if (!visualsConfig.screenEffect)
        return;

    const auto material = interfaces->materialSystem->findMaterial([] {
        constexpr std::array effects{
            "effects/dronecam",
            "effects/underwater_overlay",
            "effects/healthboost",
            "effects/dangerzone_screen"
        };

        if (visualsConfig.screenEffect <= 2 || static_cast<std::size_t>(visualsConfig.screenEffect - 2) >= effects.size())
            return effects[0];
        return effects[visualsConfig.screenEffect - 2];
        }());

    if (visualsConfig.screenEffect == 1)
        material->findVar("$c0_x")->setValue(0.0f);
    else if (visualsConfig.screenEffect == 2)
        material->findVar("$c0_x")->setValue(0.1f);
    else if (visualsConfig.screenEffect >= 4)
        material->findVar("$c0_x")->setValue(1.0f);

    DRAW_SCREEN_EFFECT(material)
}

void Visuals::hitEffect(GameEvent* event) noexcept
{
    if (visualsConfig.hitEffect && localPlayer) {
        static float lastHitTime = 0.0f;

        if (event && interfaces->engine->getPlayerForUserID(event->getInt("attacker")) == localPlayer->index()) {
            lastHitTime = memory->globalVars->realtime;
            return;
        }

        if (lastHitTime + visualsConfig.hitEffectTime >= memory->globalVars->realtime) {
            constexpr auto getEffectMaterial = [] {
                static constexpr const char* effects[]{
                "effects/dronecam",
                "effects/underwater_overlay",
                "effects/healthboost",
                "effects/dangerzone_screen"
                };

                if (visualsConfig.hitEffect <= 2)
                    return effects[0];
                return effects[visualsConfig.hitEffect - 2];
            };


            auto material = interfaces->materialSystem->findMaterial(getEffectMaterial());
            if (visualsConfig.hitEffect == 1)
                material->findVar("$c0_x")->setValue(0.0f);
            else if (visualsConfig.hitEffect == 2)
                material->findVar("$c0_x")->setValue(0.1f);
            else if (visualsConfig.hitEffect >= 4)
                material->findVar("$c0_x")->setValue(1.0f);

            DRAW_SCREEN_EFFECT(material)
        }
    }
}

void Visuals::hitMarker(GameEvent* event, ImDrawList* drawList) noexcept
{
    if (visualsConfig.hitMarker == 0)
        return;

    static float lastHitTime = 0.0f;

    if (event) {
        if (localPlayer && event->getInt("attacker") == localPlayer->getUserId())
            lastHitTime = memory->globalVars->realtime;
        return;
    }

    if (lastHitTime + visualsConfig.hitMarkerTime < memory->globalVars->realtime)
        return;

    switch (visualsConfig.hitMarker) {
    case 1:
        const auto & mid = ImGui::GetIO().DisplaySize / 2.0f;
        constexpr auto color = IM_COL32(255, 255, 255, 255);
        drawList->AddLine({ mid.x - 10, mid.y - 10 }, { mid.x - 4, mid.y - 4 }, color);
        drawList->AddLine({ mid.x + 10.5f, mid.y - 10.5f }, { mid.x + 4.5f, mid.y - 4.5f }, color);
        drawList->AddLine({ mid.x + 10.5f, mid.y + 10.5f }, { mid.x + 4.5f, mid.y + 4.5f }, color);
        drawList->AddLine({ mid.x - 10, mid.y + 10 }, { mid.x - 4, mid.y + 4 }, color);
        break;
    }
}

void Visuals::disablePostProcessing(FrameStage stage) noexcept
{
    if (stage != FrameStage::RENDER_START && stage != FrameStage::RENDER_END)
        return;

    *memory->disablePostProcessing = stage == FrameStage::RENDER_START && visualsConfig.disablePostProcessing;
}

void Visuals::reduceFlashEffect() noexcept
{
    if (localPlayer)
        localPlayer->flashMaxAlpha() = 255.0f - visualsConfig.flashReduction * 2.55f;
}

bool Visuals::removeHands(const char* modelName) noexcept
{
    return visualsConfig.noHands && std::strstr(modelName, "arms") && !std::strstr(modelName, "sleeve");
}

bool Visuals::removeSleeves(const char* modelName) noexcept
{
    return visualsConfig.noSleeves && std::strstr(modelName, "sleeve");
}

bool Visuals::removeWeapons(const char* modelName) noexcept
{
    return visualsConfig.noWeapons && std::strstr(modelName, "models/weapons/v_")
        && !std::strstr(modelName, "arms") && !std::strstr(modelName, "tablet")
        && !std::strstr(modelName, "parachute") && !std::strstr(modelName, "fists");
}

void Visuals::skybox(FrameStage stage) noexcept
{
    if (stage != FrameStage::RENDER_START && stage != FrameStage::RENDER_END)
        return;

    if (stage == FrameStage::RENDER_START && visualsConfig.skybox > 0 && static_cast<std::size_t>(visualsConfig.skybox) < skyboxList.size()) {
        memory->loadSky(skyboxList[visualsConfig.skybox]);
    }
    else {
        static const auto sv_skyname = interfaces->cvar->findVar("sv_skyname");
        memory->loadSky(sv_skyname->string);
    }
}

void Visuals::bulletTracer(GameEvent& event) noexcept
{
    if (!visualsConfig.bulletTracers.enabled)
        return;

    if (!localPlayer)
        return;

    if (event.getInt("userid") != localPlayer->getUserId())
        return;

    const auto activeWeapon = localPlayer->getActiveWeapon();
    if (!activeWeapon)
        return;

    BeamInfo beamInfo;

    if (!localPlayer->shouldDraw()) {
        const auto viewModel = interfaces->entityList->getEntityFromHandle(localPlayer->viewModel());
        if (!viewModel)
            return;

        if (!viewModel->getAttachment(activeWeapon->getMuzzleAttachmentIndex1stPerson(viewModel), beamInfo.start))
            return;
    }
    else {
        const auto worldModel = interfaces->entityList->getEntityFromHandle(activeWeapon->weaponWorldModel());
        if (!worldModel)
            return;

        if (!worldModel->getAttachment(activeWeapon->getMuzzleAttachmentIndex3rdPerson(), beamInfo.start))
            return;
    }

    beamInfo.end.x = event.getFloat("x");
    beamInfo.end.y = event.getFloat("y");
    beamInfo.end.z = event.getFloat("z");

    beamInfo.modelName = "sprites/physbeam.vmt";
    beamInfo.modelIndex = -1;
    beamInfo.haloName = nullptr;
    beamInfo.haloIndex = -1;

    beamInfo.red = 255.0f * visualsConfig.bulletTracers.asColor4().color[0];
    beamInfo.green = 255.0f * visualsConfig.bulletTracers.asColor4().color[1];
    beamInfo.blue = 255.0f * visualsConfig.bulletTracers.asColor4().color[2];
    beamInfo.brightness = 255.0f * visualsConfig.bulletTracers.asColor4().color[3];

    beamInfo.type = 0;
    beamInfo.life = 0.0f;
    beamInfo.amplitude = 0.0f;
    beamInfo.segments = -1;
    beamInfo.renderable = true;
    beamInfo.speed = 0.2f;
    beamInfo.startFrame = 0;
    beamInfo.frameRate = 0.0f;
    beamInfo.width = 2.0f;
    beamInfo.endWidth = 2.0f;
    beamInfo.flags = 0x40;
    beamInfo.fadeLength = 20.0f;

    if (const auto beam = memory->viewRenderBeams->createBeamPoints(beamInfo)) {
        constexpr auto FBEAM_FOREVER = 0x4000;
        beam->flags &= ~FBEAM_FOREVER;
        beam->die = memory->globalVars->currenttime + 2.0f;
    }
}

void Visuals::drawMolotovHull(ImDrawList* drawList) noexcept
{
    if (!visualsConfig.molotovHull.enabled)
        return;

    const auto color = Helpers::calculateColor(visualsConfig.molotovHull.asColor4());

    GameData::Lock lock;

    static const auto flameCircumference = [] {
        std::array<Vector, 72> points;
        for (std::size_t i = 0; i < points.size(); ++i) {
            constexpr auto flameRadius = 60.0f; // https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/game/server/cstrike15/Effects/inferno.cpp#L889
            points[i] = Vector{ flameRadius * std::cos(Helpers::deg2rad(i * (360.0f / points.size()))),
                                flameRadius * std::sin(Helpers::deg2rad(i * (360.0f / points.size()))),
                                0.0f };
        }
        return points;
    }();

    for (const auto& molotov : GameData::infernos()) {
        for (const auto& pos : molotov.points) {
            std::array<ImVec2, flameCircumference.size()> screenPoints;
            std::size_t count = 0;

            for (const auto& point : flameCircumference) {
                if (Helpers::worldToScreen(pos + point, screenPoints[count]))
                    ++count;
            }

            if (count < 1)
                continue;

            std::swap(screenPoints[0], *std::min_element(screenPoints.begin(), screenPoints.begin() + count, [](const auto& a, const auto& b) { return a.y < b.y || (a.y == b.y && a.x < b.x); }));

            constexpr auto orientation = [](const ImVec2& a, const ImVec2& b, const ImVec2& c) {
                return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
            };

            std::sort(screenPoints.begin() + 1, screenPoints.begin() + count, [&](const auto& a, const auto& b) { return orientation(screenPoints[0], a, b) > 0.0f; });
            drawList->AddConvexPolyFilled(screenPoints.data(), count, color);
        }
    }
}

void Visuals::updateEventListeners(bool forceRemove) noexcept
{
    class ImpactEventListener : public GameEventListener {
    public:
        void fireGameEvent(GameEvent* event) override { bulletTracer(*event); }
    };

    static ImpactEventListener listener;
    static bool listenerRegistered = false;

    if (visualsConfig.bulletTracers.enabled && !listenerRegistered) {
        interfaces->gameEventManager->addListener(&listener, "bullet_impact");
        listenerRegistered = true;
    }
    else if ((!visualsConfig.bulletTracers.enabled || forceRemove) && listenerRegistered) {
        interfaces->gameEventManager->removeListener(&listener);
        listenerRegistered = false;
    }
}

void Visuals::updateInput() noexcept
{
    visualsConfig.thirdpersonKey.handleToggle();
    visualsConfig.zoomKey.handleToggle();
}

static bool windowOpen = false;


json Visuals::toJson() noexcept
{
    json j;
    to_json(j, visualsConfig);
    return j;
}

void Visuals::fromJson(const json& j) noexcept
{
    from_json(j, visualsConfig);
}

void Visuals::resetConfig() noexcept
{
    visualsConfig = {};
}

static constexpr auto operator-(float sub, const std::array<float, 3>& a) noexcept
{
    return Vector{ sub - a[0], sub - a[1], sub - a[2] };
}

struct BoundingBox {
private:
    bool valid;
public:
    ImVec2 min, max;
    std::array<ImVec2, 8> vertices;

    BoundingBox(const Vector& mins, const Vector& maxs, const std::array<float, 3>& scale, const matrix3x4* matrix = nullptr) noexcept
    {
        min.y = min.x = std::numeric_limits<float>::max();
        max.y = max.x = -std::numeric_limits<float>::max();

        const auto scaledMins = mins + (maxs - mins) * 2 * (0.25f - scale);
        const auto scaledMaxs = maxs - (maxs - mins) * 2 * (0.25f - scale);

        for (int i = 0; i < 8; ++i) {
            const Vector point{ i & 1 ? scaledMaxs.x : scaledMins.x,
                                i & 2 ? scaledMaxs.y : scaledMins.y,
                                i & 4 ? scaledMaxs.z : scaledMins.z };

            if (!Helpers::worldToScreenPixelAligned(matrix ? point.transform(*matrix) : point, vertices[i])) {
                valid = false;
                return;
            }

            min.x = std::min(min.x, vertices[i].x);
            min.y = std::min(min.y, vertices[i].y);
            max.x = std::max(max.x, vertices[i].x);
            max.y = std::max(max.y, vertices[i].y);
        }
        valid = true;
    }

    BoundingBox(const BaseData& data, const std::array<float, 3>& scale) noexcept : BoundingBox{ data.obbMins, data.obbMaxs, scale, &data.coordinateFrame } {}
    BoundingBox(const Vector& center) noexcept : BoundingBox{ center - 2.0f, center + 2.0f, { 0.25f, 0.25f, 0.25f } } {}

    explicit operator bool() const noexcept
    {
        return valid;
    }
};

static ImDrawList* drawList;

static void addLineWithShadow(const ImVec2& p1, const ImVec2& p2, ImU32 col) noexcept
{
    drawList->AddLine(p1 + ImVec2{ 1.0f, 1.0f }, p2 + ImVec2{ 1.0f, 1.0f }, col & IM_COL32_A_MASK);
    drawList->AddLine(p1, p2, col);
}

// convex hull using Graham's scan
static std::pair<std::array<ImVec2, 8>, std::size_t> convexHull(std::array<ImVec2, 8> points) noexcept
{
    std::swap(points[0], *std::ranges::min_element(points, [](const auto& a, const auto& b) { return a.y < b.y || (a.y == b.y && a.x < b.x); }));

    constexpr auto orientation = [](const ImVec2& a, const ImVec2& b, const ImVec2& c) {
        return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    };

    std::sort(points.begin() + 1, points.end(), [&](const auto& a, const auto& b) {
        const auto o = orientation(points[0], a, b);
        return o == 0.0f ? ImLengthSqr(points[0] - a) < ImLengthSqr(points[0] - b) : o < 0.0f;
        });

    std::array<ImVec2, 8> hull;
    std::size_t count = 0;

    for (const auto& p : points) {
        while (count >= 2 && orientation(hull[count - 2], hull[count - 1], p) >= 0.0f)
            --count;
        hull[count++] = p;
    }

    return std::make_pair(hull, count);
}

static void addRectFilled(const ImVec2& p1, const ImVec2& p2, ImU32 col, bool shadow) noexcept
{
    if (shadow)
        drawList->AddRectFilled(p1 + ImVec2{ 1.0f, 1.0f }, p2 + ImVec2{ 1.0f, 1.0f }, col & IM_COL32_A_MASK);
    drawList->AddRectFilled(p1, p2, col);
}

static void renderBox(const BoundingBox& bbox, const Box& config) noexcept
{
    if (!config.enabled)
        return;

    const ImU32 color = Helpers::calculateColor(config.asColor4());
    const ImU32 fillColor = Helpers::calculateColor(config.fill.asColor4());

    switch (config.type) {
    case Box::_2d:
        if (config.fill.enabled)
            drawList->AddRectFilled(bbox.min + ImVec2{ 1.0f, 1.0f }, bbox.max - ImVec2{ 1.0f, 1.0f }, fillColor, config.rounding, ImDrawFlags_RoundCornersAll);
        else
            drawList->AddRect(bbox.min + ImVec2{ 1.0f, 1.0f }, bbox.max + ImVec2{ 1.0f, 1.0f }, color & IM_COL32_A_MASK, config.rounding, ImDrawFlags_RoundCornersAll);
        drawList->AddRect(bbox.min, bbox.max, color, config.rounding, ImDrawFlags_RoundCornersAll);
        break;
    case Box::_2dCorners: {
        if (config.fill.enabled) {
            drawList->AddRectFilled(bbox.min + ImVec2{ 1.0f, 1.0f }, bbox.max - ImVec2{ 1.0f, 1.0f }, fillColor, config.rounding, ImDrawFlags_RoundCornersAll);
        }

        const bool wantsShadow = !config.fill.enabled;

        const auto quarterWidth = IM_FLOOR((bbox.max.x - bbox.min.x) * 0.25f);
        const auto quarterHeight = IM_FLOOR((bbox.max.y - bbox.min.y) * 0.25f);

        addRectFilled(bbox.min, { bbox.min.x + 1.0f, bbox.min.y + quarterHeight }, color, wantsShadow);
        addRectFilled(bbox.min, { bbox.min.x + quarterWidth, bbox.min.y + 1.0f }, color, wantsShadow);

        addRectFilled({ bbox.max.x, bbox.min.y }, { bbox.max.x - quarterWidth, bbox.min.y + 1.0f }, color, wantsShadow);
        addRectFilled({ bbox.max.x - 1.0f, bbox.min.y }, { bbox.max.x, bbox.min.y + quarterHeight }, color, wantsShadow);

        addRectFilled({ bbox.min.x, bbox.max.y }, { bbox.min.x + 1.0f, bbox.max.y - quarterHeight }, color, wantsShadow);
        addRectFilled({ bbox.min.x, bbox.max.y - 1.0f }, { bbox.min.x + quarterWidth, bbox.max.y }, color, wantsShadow);

        addRectFilled(bbox.max, { bbox.max.x - quarterWidth, bbox.max.y - 1.0f }, color, wantsShadow);
        addRectFilled(bbox.max, { bbox.max.x - 1.0f, bbox.max.y - quarterHeight }, color, wantsShadow);
        break;
    }
    case Box::_3d:
        if (config.fill.enabled) {
            auto [hull, count] = convexHull(bbox.vertices);
            std::reverse(hull.begin(), hull.begin() + count); // make them clockwise for antialiasing
            drawList->AddConvexPolyFilled(hull.data(), count, fillColor);
        }
        else {
            for (int i = 0; i < 8; ++i) {
                for (int j = 1; j <= 4; j <<= 1) {
                    if (!(i & j))
                        drawList->AddLine(bbox.vertices[i] + ImVec2{ 1.0f, 1.0f }, bbox.vertices[i + j] + ImVec2{ 1.0f, 1.0f }, color & IM_COL32_A_MASK);
                }
            }
        }

        for (int i = 0; i < 8; ++i) {
            for (int j = 1; j <= 4; j <<= 1) {
                if (!(i & j))
                    drawList->AddLine(bbox.vertices[i], bbox.vertices[i + j], color);
            }
        }
        break;
    case Box::_3dCorners:
        if (config.fill.enabled) {
            auto [hull, count] = convexHull(bbox.vertices);
            std::reverse(hull.begin(), hull.begin() + count); // make them clockwise for antialiasing
            drawList->AddConvexPolyFilled(hull.data(), count, fillColor);
        }
        else {
            for (int i = 0; i < 8; ++i) {
                for (int j = 1; j <= 4; j <<= 1) {
                    if (!(i & j)) {
                        drawList->AddLine(bbox.vertices[i] + ImVec2{ 1.0f, 1.0f }, ImVec2{ bbox.vertices[i].x * 0.75f + bbox.vertices[i + j].x * 0.25f, bbox.vertices[i].y * 0.75f + bbox.vertices[i + j].y * 0.25f } + ImVec2{ 1.0f, 1.0f }, color & IM_COL32_A_MASK);
                        drawList->AddLine(ImVec2{ bbox.vertices[i].x * 0.25f + bbox.vertices[i + j].x * 0.75f, bbox.vertices[i].y * 0.25f + bbox.vertices[i + j].y * 0.75f } + ImVec2{ 1.0f, 1.0f }, bbox.vertices[i + j] + ImVec2{ 1.0f, 1.0f }, color & IM_COL32_A_MASK);
                    }
                }
            }
        }

        for (int i = 0; i < 8; ++i) {
            for (int j = 1; j <= 4; j <<= 1) {
                if (!(i & j)) {
                    drawList->AddLine(bbox.vertices[i], { bbox.vertices[i].x * 0.75f + bbox.vertices[i + j].x * 0.25f, bbox.vertices[i].y * 0.75f + bbox.vertices[i + j].y * 0.25f }, color);
                    drawList->AddLine({ bbox.vertices[i].x * 0.25f + bbox.vertices[i + j].x * 0.75f, bbox.vertices[i].y * 0.25f + bbox.vertices[i + j].y * 0.75f }, bbox.vertices[i + j], color);
                }
            }
        }
        break;
    }
}

static ImVec2 renderText(float distance, float cullDistance, const Color4& textCfg, const char* text, const ImVec2& pos, bool centered = true, bool adjustHeight = true) noexcept
{
    if (cullDistance && Helpers::units2meters(distance) > cullDistance)
        return { };

    const auto textSize = ImGui::CalcTextSize(text);

    const auto horizontalOffset = centered ? textSize.x / 2 : 0.0f;
    const auto verticalOffset = adjustHeight ? textSize.y : 0.0f;

    const auto color = Helpers::calculateColor(textCfg);
    drawList->AddText({ pos.x - horizontalOffset + 1.0f, pos.y - verticalOffset + 1.0f }, color & IM_COL32_A_MASK, text);
    drawList->AddText({ pos.x - horizontalOffset, pos.y - verticalOffset }, color, text);

    return textSize;
}

static void drawSnapline(const Snapline& config, const ImVec2& min, const ImVec2& max) noexcept
{
    if (!config.asColorToggle().enabled)
        return;

    const auto& screenSize = ImGui::GetIO().DisplaySize;

    ImVec2 p1, p2;
    p1.x = screenSize.x / 2;
    p2.x = (min.x + max.x) / 2;

    switch (config.type) {
    case Snapline::Bottom:
        p1.y = screenSize.y;
        p2.y = max.y;
        break;
    case Snapline::Top:
        p1.y = 0.0f;
        p2.y = min.y;
        break;
    case Snapline::Crosshair:
        p1.y = screenSize.y / 2;
        p2.y = (min.y + max.y) / 2;
        break;
    default:
        return;
    }

    drawList->AddLine(p1, p2, Helpers::calculateColor(config.asColorToggle().asColor4()), config.thickness);
}

struct FontPush {
    FontPush(const std::string& name, float distance)
    {
        if (const auto it = config->getFonts().find(name); it != config->getFonts().end()) {
            distance *= GameData::local().fov / 90.0f;

            ImGui::PushFont([](const Config::Font& font, float dist) {
                if (dist <= 400.0f)
                    return font.big;
                if (dist <= 1000.0f)
                    return font.medium;
                return font.tiny;
                }(it->second, distance));
        }
        else {
            ImGui::PushFont(nullptr);
        }
    }

    ~FontPush()
    {
        ImGui::PopFont();
    }
};

static void drawHealthBar(const HealthBar& config, const ImVec2& pos, float height, int health) noexcept
{
    if (!config.enabled)
        return;

    constexpr float width = 3.0f;

    drawList->PushClipRect(pos + ImVec2{ 0.0f, (100 - health) / 100.0f * height }, pos + ImVec2{ width + 1.0f, height + 1.0f });

    if (config.type == HealthBar::Gradient) {
        const auto green = Helpers::calculateColor(0, 255, 0, 255);
        const auto yellow = Helpers::calculateColor(255, 255, 0, 255);
        const auto red = Helpers::calculateColor(255, 0, 0, 255);

        ImVec2 min = pos;
        ImVec2 max = min + ImVec2{ width, height / 2.0f };

        drawList->AddRectFilled(min + ImVec2{ 1.0f, 1.0f }, pos + ImVec2{ width + 1.0f, height + 1.0f }, Helpers::calculateColor(0, 0, 0, 255));

        drawList->AddRectFilledMultiColor(ImFloor(min), ImFloor(max), green, green, yellow, yellow);
        min.y += height / 2.0f;
        max.y += height / 2.0f;
        drawList->AddRectFilledMultiColor(ImFloor(min), ImFloor(max), yellow, yellow, red, red);
    }
    else {
        const auto color = config.type == HealthBar::HealthBased ? Helpers::healthColor(std::clamp(health / 100.0f, 0.0f, 1.0f)) : Helpers::calculateColor(config.asColor4());
        drawList->AddRectFilled(pos + ImVec2{ 1.0f, 1.0f }, pos + ImVec2{ width + 1.0f, height + 1.0f }, color & IM_COL32_A_MASK);
        drawList->AddRectFilled(pos, pos + ImVec2{ width, height }, color);
    }

    drawList->PopClipRect();
}

static void renderPlayerBox(const PlayerData& playerData, const Player& config) noexcept
{
    const BoundingBox bbox{ playerData, config.box.scale };

    if (!bbox)
        return;

    renderBox(bbox, config.box);

    ImVec2 offsetMins{}, offsetMaxs{};

    drawHealthBar(config.healthBar, bbox.min - ImVec2{ 5.0f, 0.0f }, (bbox.max.y - bbox.min.y), playerData.health);

    FontPush font{ config.font.name, playerData.distanceToLocal };

    if (config.name.enabled) {
        const auto nameSize = renderText(playerData.distanceToLocal, config.textCullDistance, config.name.asColor4(), playerData.name.c_str(), { (bbox.min.x + bbox.max.x) / 2, bbox.min.y - 2 });
        offsetMins.y -= nameSize.y + 2;
    }

    if (config.flashDuration.enabled && playerData.flashDuration > 0.0f) {
        const auto radius = std::max(5.0f - playerData.distanceToLocal / 600.0f, 1.0f);
        ImVec2 flashDurationPos{ (bbox.min.x + bbox.max.x) / 2, bbox.min.y + offsetMins.y - radius * 1.5f };

        const auto color = Helpers::calculateColor(config.flashDuration.asColor4());
        constexpr float pi = std::numbers::pi_v<float>;
        drawList->PathArcTo(flashDurationPos + ImVec2{ 1.0f, 1.0f }, radius, pi / 2 - (playerData.flashDuration / 255.0f * pi), pi / 2 + (playerData.flashDuration / 255.0f * pi), 40);
        drawList->PathStroke(color & IM_COL32_A_MASK, false, 0.9f + radius * 0.1f);

        drawList->PathArcTo(flashDurationPos, radius, pi / 2 - (playerData.flashDuration / 255.0f * pi), pi / 2 + (playerData.flashDuration / 255.0f * pi), 40);
        drawList->PathStroke(color, false, 0.9f + radius * 0.1f);

        offsetMins.y -= radius * 2.5f;
    }

    if (config.weapon.enabled && !playerData.activeWeapon.empty()) {
        const auto weaponTextSize = renderText(playerData.distanceToLocal, config.textCullDistance, config.weapon.asColor4(), playerData.activeWeapon.c_str(), { (bbox.min.x + bbox.max.x) / 2, bbox.max.y + 1 }, true, false);
        offsetMaxs.y += weaponTextSize.y + 2.0f;
    }

    drawSnapline(config.snapline, bbox.min + offsetMins, bbox.max + offsetMaxs);

}

static void renderWeaponBox(const WeaponData& weaponData, const Weapon& config) noexcept
{
    const BoundingBox bbox{ weaponData, config.box.scale };

    if (!bbox)
        return;

    renderBox(bbox, config.box);
    drawSnapline(config.snapline, bbox.min, bbox.max);

    FontPush font{ config.font.name, weaponData.distanceToLocal };

    if (config.name.enabled && !weaponData.displayName.empty()) {
        renderText(weaponData.distanceToLocal, config.textCullDistance, config.name.asColor4(), weaponData.displayName.c_str(), { (bbox.min.x + bbox.max.x) / 2, bbox.min.y - 2 });
    }

    if (config.ammo.enabled && weaponData.clip != -1) {
        const auto text{ std::to_string(weaponData.clip) + " / " + std::to_string(weaponData.reserveAmmo) };
        renderText(weaponData.distanceToLocal, config.textCullDistance, config.ammo.asColor4(), text.c_str(), { (bbox.min.x + bbox.max.x) / 2, bbox.max.y + 1 }, true, false);
    }
}

static void renderEntityBox(const BaseData& entityData, const char* name, const Shared& config) noexcept
{
    const BoundingBox bbox{ entityData, config.box.scale };

    if (!bbox)
        return;

    renderBox(bbox, config.box);
    drawSnapline(config.snapline, bbox.min, bbox.max);

    FontPush font{ config.font.name, entityData.distanceToLocal };

    if (config.name.enabled)
        renderText(entityData.distanceToLocal, config.textCullDistance, config.name.asColor4(), name, { (bbox.min.x + bbox.max.x) / 2, bbox.min.y - 5 });
}

static void drawProjectileTrajectory(const Trail& config, const std::vector<std::pair<float, Vector>>& trajectory) noexcept
{
    if (!config.asColorToggle().enabled)
        return;

    std::vector<ImVec2> points, shadowPoints;

    const auto color = Helpers::calculateColor(config.asColorToggle().asColor4());

    for (const auto& [time, point] : trajectory) {
        if (ImVec2 pos; time + config.time >= memory->globalVars->realtime && Helpers::worldToScreen(point, pos)) {
            if (config.type == Trail::Line) {
                points.push_back(pos);
                shadowPoints.push_back(pos + ImVec2{ 1.0f, 1.0f });
            }
            else if (config.type == Trail::Circles) {
                drawList->AddCircle(pos, 3.5f - point.distTo(GameData::local().origin) / 700.0f, color, 12, config.thickness);
            }
            else if (config.type == Trail::FilledCircles) {
                drawList->AddCircleFilled(pos, 3.5f - point.distTo(GameData::local().origin) / 700.0f, color);
            }
        }
    }

    if (config.type == Trail::Line) {
        drawList->AddPolyline(shadowPoints.data(), shadowPoints.size(), color & IM_COL32_A_MASK, false, config.thickness);
        drawList->AddPolyline(points.data(), points.size(), color, false, config.thickness);
    }
}

static void drawPlayerSkeleton(const ColorToggleThickness& config, const std::vector<std::pair<Vector, Vector>>& bones) noexcept
{
    if (!config.asColorToggle().enabled)
        return;

    const auto color = Helpers::calculateColor(config.asColorToggle().asColor4());

    std::vector<std::pair<ImVec2, ImVec2>> points, shadowPoints;

    for (const auto& [bone, parent] : bones) {
        ImVec2 bonePoint;
        if (!Helpers::worldToScreenPixelAligned(bone, bonePoint))
            continue;

        ImVec2 parentPoint;
        if (!Helpers::worldToScreenPixelAligned(parent, parentPoint))
            continue;

        points.emplace_back(bonePoint, parentPoint);
        shadowPoints.emplace_back(bonePoint + ImVec2{ 1.0f, 1.0f }, parentPoint + ImVec2{ 1.0f, 1.0f });
    }

    for (const auto& [bonePoint, parentPoint] : shadowPoints)
        drawList->AddLine(bonePoint, parentPoint, color & IM_COL32_A_MASK, config.thickness);

    for (const auto& [bonePoint, parentPoint] : points)
        drawList->AddLine(bonePoint, parentPoint, color, config.thickness);
}

static bool renderPlayerEsp(const PlayerData& playerData, const Player& playerConfig) noexcept
{
    if (!playerConfig.enabled)
        return false;

    if (playerConfig.audibleOnly && !playerData.audible && !playerConfig.spottedOnly
        || playerConfig.spottedOnly && !playerData.spotted && !(playerConfig.audibleOnly && playerData.audible)) // if both "Audible Only" and "Spotted Only" are on treat them as audible OR spotted
        return true;

    if (playerData.immune)
        Helpers::setAlphaFactor(0.5f);

    Helpers::setAlphaFactor(Helpers::getAlphaFactor() * playerData.fadingAlpha());

    renderPlayerBox(playerData, playerConfig);
    drawPlayerSkeleton(playerConfig.skeleton, playerData.bones);

    if (const BoundingBox headBbox{ playerData.headMins, playerData.headMaxs, playerConfig.headBox.scale })
        renderBox(headBbox, playerConfig.headBox);

    Helpers::setAlphaFactor(1.0f);

    return true;
}

static void renderWeaponEsp(const WeaponData& weaponData, const Weapon& parentConfig, const Weapon& itemConfig) noexcept
{
    const auto& config = itemConfig.enabled ? itemConfig : (parentConfig.enabled ? parentConfig : ::config->streamProofESP.weapons["All"]);
    if (config.enabled) {
        renderWeaponBox(weaponData, config);
    }
}

static void renderEntityEsp(const BaseData& entityData, const std::unordered_map<std::string, Shared>& map, const char* name) noexcept
{
    if (const auto cfg = map.find(name); cfg != map.cend() && cfg->second.enabled) {
        renderEntityBox(entityData, name, cfg->second);
    }
    else if (const auto cfg = map.find("All"); cfg != map.cend() && cfg->second.enabled) {
        renderEntityBox(entityData, name, cfg->second);
    }
}

static void renderProjectileEsp(const ProjectileData& projectileData, const Projectile& parentConfig, const Projectile& itemConfig, const char* name) noexcept
{
    const auto& config = itemConfig.enabled ? itemConfig : parentConfig;

    if (config.enabled) {
        if (!projectileData.exploded)
            renderEntityBox(projectileData, name, config);

        if (config.trails.enabled) {
            if (projectileData.thrownByLocalPlayer)
                drawProjectileTrajectory(config.trails.localPlayer, projectileData.trajectory);
            else if (!projectileData.thrownByEnemy)
                drawProjectileTrajectory(config.trails.allies, projectileData.trajectory);
            else
                drawProjectileTrajectory(config.trails.enemies, projectileData.trajectory);
        }
    }
}

void StreamProofESP::render() noexcept
{
    if (config->streamProofESP.toggleKey.isSet()) {
        if (!config->streamProofESP.toggleKey.isToggled() && !config->streamProofESP.holdKey.isDown())
            return;
    }
    else if (config->streamProofESP.holdKey.isSet() && !config->streamProofESP.holdKey.isDown()) {
        return;
    }

    drawList = ImGui::GetBackgroundDrawList();

    GameData::Lock lock;

    for (const auto& weapon : GameData::weapons())
        renderWeaponEsp(weapon, config->streamProofESP.weapons[weapon.group], config->streamProofESP.weapons[weapon.name]);

    for (const auto& entity : GameData::entities())
        renderEntityEsp(entity, config->streamProofESP.otherEntities, entity.name);

    for (const auto& lootCrate : GameData::lootCrates()) {
        if (lootCrate.name)
            renderEntityEsp(lootCrate, config->streamProofESP.lootCrates, lootCrate.name);
    }

    for (const auto& projectile : GameData::projectiles())
        renderProjectileEsp(projectile, config->streamProofESP.projectiles["All"], config->streamProofESP.projectiles[projectile.name], projectile.name);

    for (const auto& player : GameData::players()) {
        if ((player.dormant && player.fadingAlpha() == 0.0f) || !player.alive || !player.inViewFrustum)
            continue;

        auto& playerConfig = player.enemy ? config->streamProofESP.enemies : config->streamProofESP.allies;

        if (!renderPlayerEsp(player, playerConfig["All"]))
            renderPlayerEsp(player, playerConfig[player.visible ? "Visible" : "Occluded"]);
    }
}

void StreamProofESP::updateInput() noexcept
{
    config->streamProofESP.toggleKey.handleToggle();
}




struct PreserveKillfeed {
    bool enabled = false;
    bool onlyHeadshots = false;
};

struct OffscreenEnemies : ColorToggle {
    OffscreenEnemies() : ColorToggle{ 1.0f, 0.26f, 0.21f, 1.0f } {}
    HealthBar healthBar;
};

struct PurchaseList {
    bool enabled = false;
    bool onlyDuringFreezeTime = false;
    bool showPrices = false;
    bool noTitleBar = false;

    enum Mode {
        Details = 0,
        Summary
    };
    int mode = Details;
};

struct MiscConfig {
    MiscConfig() { clanTag[0] = '\0'; }

    KeyBind menuKey{ KeyBind::INSERT };
    bool antiAfkKick{ false };
    bool autoStrafe{ false };
    bool bunnyHop{ false };
    bool customClanTag{ false };
    bool clocktag{ false };
    bool animatedClanTag{ false };
    bool fastDuck{ false };
    bool moonwalk{ false };
    bool edgejump{ false };
    bool slowwalk{ false };
    bool autoPistol{ false };
    bool autoReload{ false };
    bool autoAccept{ false };
    bool radarHack{ false };
    bool revealRanks{ false };
    bool revealMoney{ false };
    bool revealSuspect{ false };
    bool revealVotes{ false };
    bool fixAnimationLOD{ false };
    bool fixBoneMatrix{ false };
    bool fixMovement{ false };
    bool disableModelOcclusion{ false };
    bool nameStealer{ false };
    bool disablePanoramablur{ false };
    bool killMessage{ false };
    bool nadePredict{ false };
    bool fixTabletSignal{ false };
    bool fastPlant{ false };
    bool fastStop{ false };
    bool quickReload{ false };
    bool prepareRevolver{ false };
    bool oppositeHandKnife = false;
    PreserveKillfeed preserveKillfeed;
    char clanTag[16];
    KeyBind edgejumpkey;
    KeyBind slowwalkKey;
    ColorToggleThickness noscopeCrosshair;
    ColorToggleThickness recoilCrosshair;

    struct SpectatorList {
        bool enabled = false;
        bool noTitleBar = false;
        ImVec2 pos;
        ImVec2 size{ 200.0f, 200.0f };
    };

    SpectatorList spectatorList;
    struct Watermark {
        bool enabled = false;
    };
    Watermark watermark;
    float aspectratio{ 0 };
    std::string killMessageString{ "Gotcha!" };
    int banColor{ 6 };
    std::string banText{ "Cheater has been permanently banned from official CS:GO servers." };
    ColorToggle3 bombTimer{ 1.0f, 0.55f, 0.0f };
    KeyBind prepareRevolverKey;
    int hitSound{ 0 };
    int chokedPackets{ 0 };
    KeyBind chokedPacketsKey;
    int quickHealthshotKey{ 0 };
    float maxAngleDelta{ 255.0f };
    int killSound{ 0 };
    std::string customKillSound;
    std::string customHitSound;
    PurchaseList purchaseList;

    struct Reportbot {
        bool enabled = false;
        bool textAbuse = false;
        bool griefing = false;
        bool wallhack = true;
        bool aimbot = true;
        bool other = true;
        int target = 0;
        int delay = 1;
        int rounds = 1;
    } reportbot;

    OffscreenEnemies offscreenEnemies;
} miscConfig;

bool Misc::shouldRevealMoney() noexcept
{
    return miscConfig.revealMoney;
}

bool Misc::shouldRevealSuspect() noexcept
{
    return miscConfig.revealSuspect;
}

bool Misc::shouldDisableModelOcclusion() noexcept
{
    return miscConfig.disableModelOcclusion;
}

bool Misc::shouldFixBoneMatrix() noexcept
{
    return miscConfig.fixBoneMatrix;
}

bool Misc::isRadarHackOn() noexcept
{
    return miscConfig.radarHack;
}

bool Misc::isMenuKeyPressed() noexcept
{
    return miscConfig.menuKey.isPressed();
}

float Misc::maxAngleDelta() noexcept
{
    return miscConfig.maxAngleDelta;
}

float Misc::aspectRatio() noexcept
{
    return miscConfig.aspectratio;
}

void Misc::edgejump(UserCmd* cmd) noexcept
{
    if (!miscConfig.edgejump || !miscConfig.edgejumpkey.isDown())
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    if (const auto mt = localPlayer->moveType(); mt == MoveType::LADDER || mt == MoveType::NOCLIP)
        return;

    if ((EnginePrediction::getFlags() & 1) && !(localPlayer->flags() & 1))
        cmd->buttons |= UserCmd::IN_JUMP;
}

void Misc::slowwalk(UserCmd* cmd) noexcept
{
    if (!miscConfig.slowwalk || !miscConfig.slowwalkKey.isDown())
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    const auto activeWeapon = localPlayer->getActiveWeapon();
    if (!activeWeapon)
        return;

    const auto weaponData = activeWeapon->getWeaponData();
    if (!weaponData)
        return;

    const float maxSpeed = (localPlayer->isScoped() ? weaponData->maxSpeedAlt : weaponData->maxSpeed) / 3;

    if (cmd->forwardmove && cmd->sidemove) {
        const float maxSpeedRoot = maxSpeed * static_cast<float>(M_SQRT1_2);
        cmd->forwardmove = cmd->forwardmove < 0.0f ? -maxSpeedRoot : maxSpeedRoot;
        cmd->sidemove = cmd->sidemove < 0.0f ? -maxSpeedRoot : maxSpeedRoot;
    }
    else if (cmd->forwardmove) {
        cmd->forwardmove = cmd->forwardmove < 0.0f ? -maxSpeed : maxSpeed;
    }
    else if (cmd->sidemove) {
        cmd->sidemove = cmd->sidemove < 0.0f ? -maxSpeed : maxSpeed;
    }
}

void Misc::updateClanTag(bool tagChanged) noexcept
{
    static std::string clanTag;

    if (tagChanged) {
        clanTag = miscConfig.clanTag;
        if (!clanTag.empty() && clanTag.front() != ' ' && clanTag.back() != ' ')
            clanTag.push_back(' ');
        return;
    }

    static auto lastTime = 0.0f;

    if (miscConfig.clocktag) {
        if (memory->globalVars->realtime - lastTime < 1.0f)
            return;

        const auto time = std::time(nullptr);
        const auto localTime = std::localtime(&time);
        char s[11];
        s[0] = '\0';
        snprintf(s, sizeof(s), "[%02d:%02d:%02d]", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
        lastTime = memory->globalVars->realtime;
        memory->setClanTag(s, s);
    }
    else if (miscConfig.customClanTag) {
        if (memory->globalVars->realtime - lastTime < 0.6f)
            return;

        if (miscConfig.animatedClanTag && !clanTag.empty()) {
            if (const auto offset = Helpers::utf8SeqLen(clanTag[0]); offset <= clanTag.length())
                std::rotate(clanTag.begin(), clanTag.begin() + offset, clanTag.end());
        }
        lastTime = memory->globalVars->realtime;
        memory->setClanTag(clanTag.c_str(), clanTag.c_str());
    }
}

void Misc::spectatorList() noexcept
{
    if (!miscConfig.spectatorList.enabled)
        return;

    GameData::Lock lock;

    const auto& observers = GameData::observers();

    if (std::ranges::none_of(observers, [](const auto& obs) { return obs.targetIsLocalPlayer; }) && !gui->isOpen())
        return;

    if (miscConfig.spectatorList.pos != ImVec2{}) {
        ImGui::SetNextWindowPos(miscConfig.spectatorList.pos);
        miscConfig.spectatorList.pos = {};
    }

    if (miscConfig.spectatorList.size != ImVec2{}) {
        ImGui::SetNextWindowSize(ImClamp(miscConfig.spectatorList.size, {}, ImGui::GetIO().DisplaySize));
        miscConfig.spectatorList.size = {};
    }

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;
    if (!gui->isOpen())
        windowFlags |= ImGuiWindowFlags_NoInputs;
    if (miscConfig.spectatorList.noTitleBar)
        windowFlags |= ImGuiWindowFlags_NoTitleBar;

    if (!gui->isOpen())
        ImGui::PushStyleColor(ImGuiCol_TitleBg, ImGui::GetColorU32(ImGuiCol_TitleBgActive));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, { 0.5f, 0.5f });
    ImGui::Begin("Spectator list", nullptr, windowFlags);
    ImGui::PopStyleVar();

    if (!gui->isOpen())
        ImGui::PopStyleColor();

    for (const auto& observer : observers) {
        if (!observer.targetIsLocalPlayer)
            continue;

        if (const auto it = std::ranges::find(GameData::players(), observer.playerHandle, &PlayerData::handle); it != GameData::players().cend()) {
            if (const auto texture = it->getAvatarTexture()) {
                const auto textSize = ImGui::CalcTextSize(it->name.c_str());
                ImGui::Image(texture, ImVec2(textSize.y, textSize.y), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(1, 1, 1, 0.3f));
                ImGui::SameLine();
                ImGui::TextWrapped("%s", it->name.c_str());
            }
        }
    }

    ImGui::End();
}

static void drawCrosshair(ImDrawList* drawList, const ImVec2& pos, ImU32 color) noexcept
{
    // dot
    drawList->AddRectFilled(pos - ImVec2{ 1, 1 }, pos + ImVec2{ 2, 2 }, color & IM_COL32_A_MASK);
    drawList->AddRectFilled(pos, pos + ImVec2{ 1, 1 }, color);

    // left
    drawList->AddRectFilled(ImVec2{ pos.x - 11, pos.y - 1 }, ImVec2{ pos.x - 3, pos.y + 2 }, color & IM_COL32_A_MASK);
    drawList->AddRectFilled(ImVec2{ pos.x - 10, pos.y }, ImVec2{ pos.x - 4, pos.y + 1 }, color);

    // right
    drawList->AddRectFilled(ImVec2{ pos.x + 4, pos.y - 1 }, ImVec2{ pos.x + 12, pos.y + 2 }, color & IM_COL32_A_MASK);
    drawList->AddRectFilled(ImVec2{ pos.x + 5, pos.y }, ImVec2{ pos.x + 11, pos.y + 1 }, color);

    // top (left with swapped x/y offsets)
    drawList->AddRectFilled(ImVec2{ pos.x - 1, pos.y - 11 }, ImVec2{ pos.x + 2, pos.y - 3 }, color & IM_COL32_A_MASK);
    drawList->AddRectFilled(ImVec2{ pos.x, pos.y - 10 }, ImVec2{ pos.x + 1, pos.y - 4 }, color);

    // bottom (right with swapped x/y offsets)
    drawList->AddRectFilled(ImVec2{ pos.x - 1, pos.y + 4 }, ImVec2{ pos.x + 2, pos.y + 12 }, color & IM_COL32_A_MASK);
    drawList->AddRectFilled(ImVec2{ pos.x, pos.y + 5 }, ImVec2{ pos.x + 1, pos.y + 11 }, color);
}

void Misc::noscopeCrosshair(ImDrawList* drawList) noexcept
{
    if (!miscConfig.noscopeCrosshair.asColorToggle().enabled)
        return;

    {
        GameData::Lock lock;
        if (const auto& local = GameData::local(); !local.exists || !local.alive || !local.noScope)
            return;
    }

    drawCrosshair(drawList, ImGui::GetIO().DisplaySize / 2, Helpers::calculateColor(miscConfig.noscopeCrosshair.asColorToggle().asColor4()));
}

void Misc::recoilCrosshair(ImDrawList* drawList) noexcept
{
    if (!miscConfig.recoilCrosshair.asColorToggle().enabled)
        return;

    GameData::Lock lock;
    const auto& localPlayerData = GameData::local();

    if (!localPlayerData.exists || !localPlayerData.alive)
        return;

    if (!localPlayerData.shooting)
        return;

    if (ImVec2 pos; Helpers::worldToScreenPixelAligned(localPlayerData.aimPunch, pos))
        drawCrosshair(drawList, pos, Helpers::calculateColor(miscConfig.recoilCrosshair.asColorToggle().asColor4()));
}

void Misc::watermark() noexcept
{
    if (!miscConfig.watermark.enabled)
        return;

    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
    if (!gui->isOpen())
        windowFlags |= ImGuiWindowFlags_NoInputs;

    ImGui::SetNextWindowBgAlpha(0.3f);
    ImGui::Begin("Watermark", nullptr, windowFlags);

    static auto frameRate = 1.0f;
    frameRate = 0.9f * frameRate + 0.1f * memory->globalVars->absoluteFrameTime;

    ImGui::Text("benzoboyz owns ur mum", frameRate != 0.0f ? static_cast<int>(1 / frameRate) : 0, GameData::getNetOutgoingLatency());
    ImGui::End();
}

void Misc::prepareRevolver(UserCmd* cmd) noexcept
{
    constexpr auto timeToTicks = [](float time) {  return static_cast<int>(0.5f + time / memory->globalVars->intervalPerTick); };
    constexpr float revolverPrepareTime{ 0.234375f };

    static float readyTime;
    if (miscConfig.prepareRevolver && localPlayer && (!miscConfig.prepareRevolverKey.isSet() || miscConfig.prepareRevolverKey.isDown())) {
        const auto activeWeapon = localPlayer->getActiveWeapon();
        if (activeWeapon && activeWeapon->itemDefinitionIndex() == WeaponId::Revolver) {
            if (!readyTime) readyTime = memory->globalVars->serverTime() + revolverPrepareTime;
            auto ticksToReady = timeToTicks(readyTime - memory->globalVars->serverTime() - interfaces->engine->getNetworkChannel()->getLatency(0));
            if (ticksToReady > 0 && ticksToReady <= timeToTicks(revolverPrepareTime))
                cmd->buttons |= UserCmd::IN_ATTACK;
            else
                readyTime = 0.0f;
        }
    }
}

void Misc::fastPlant(UserCmd* cmd) noexcept
{
    if (!miscConfig.fastPlant)
        return;

    if (static auto plantAnywhere = interfaces->cvar->findVar("mp_plant_c4_anywhere"); plantAnywhere->getInt())
        return;

    if (!localPlayer || !localPlayer->isAlive() || (localPlayer->inBombZone() && localPlayer->flags() & 1))
        return;

    if (const auto activeWeapon = localPlayer->getActiveWeapon(); !activeWeapon || activeWeapon->getClientClass()->classId != ClassId::C4)
        return;

    cmd->buttons &= ~UserCmd::IN_ATTACK;

    constexpr auto doorRange = 200.0f;

    Trace trace;
    const auto startPos = localPlayer->getEyePosition();
    const auto endPos = startPos + Vector::fromAngle(cmd->viewangles) * doorRange;
    interfaces->engineTrace->traceRay({ startPos, endPos }, 0x46004009, localPlayer.get(), trace);

    if (!trace.entity || trace.entity->getClientClass()->classId != ClassId::PropDoorRotating)
        cmd->buttons &= ~UserCmd::IN_USE;
}

void Misc::fastStop(UserCmd* cmd) noexcept
{
    if (!miscConfig.fastStop)
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    if (localPlayer->moveType() == MoveType::NOCLIP || localPlayer->moveType() == MoveType::LADDER || !(localPlayer->flags() & 1) || cmd->buttons & UserCmd::IN_JUMP)
        return;

    if (cmd->buttons & (UserCmd::IN_MOVELEFT | UserCmd::IN_MOVERIGHT | UserCmd::IN_FORWARD | UserCmd::IN_BACK))
        return;

    const auto velocity = localPlayer->velocity();
    const auto speed = velocity.length2D();
    if (speed < 15.0f)
        return;

    Vector direction = velocity.toAngle();
    direction.y = cmd->viewangles.y - direction.y;

    const auto negatedDirection = Vector::fromAngle(direction) * -speed;
    cmd->forwardmove = negatedDirection.x;
    cmd->sidemove = negatedDirection.y;
}

void Misc::drawBombTimer() noexcept
{
    if (!miscConfig.bombTimer.enabled)
        return;

    GameData::Lock lock;

    const auto& plantedC4 = GameData::plantedC4();
    if (plantedC4.blowTime == 0.0f && !gui->isOpen())
        return;

    if (!gui->isOpen()) {
        ImGui::SetNextWindowBgAlpha(0.3f);
    }

    static float windowWidth = 200.0f;
    ImGui::SetNextWindowPos({ (ImGui::GetIO().DisplaySize.x - 200.0f) / 2.0f, 60.0f }, ImGuiCond_Once);
    ImGui::SetNextWindowSize({ windowWidth, 0 }, ImGuiCond_Once);

    if (!gui->isOpen())
        ImGui::SetNextWindowSize({ windowWidth, 0 });

    ImGui::SetNextWindowSizeConstraints({ 0, -1 }, { FLT_MAX, -1 });
    ImGui::Begin("Bomb Timer", nullptr, ImGuiWindowFlags_NoTitleBar | (gui->isOpen() ? 0 : ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDecoration));

    std::ostringstream ss; ss << "Bomb on " << (!plantedC4.bombsite ? 'A' : 'B') << " : " << std::fixed << std::showpoint << std::setprecision(3) << (std::max)(plantedC4.blowTime - memory->globalVars->currenttime, 0.0f) << " s";

    ImGui::textUnformattedCentered(ss.str().c_str());

    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, Helpers::calculateColor(miscConfig.bombTimer.asColor3()));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f });
    ImGui::progressBarFullWidth((plantedC4.blowTime - memory->globalVars->currenttime) / plantedC4.timerLength, 5.0f);

    if (plantedC4.defuserHandle != -1) {
        const bool canDefuse = plantedC4.blowTime >= plantedC4.defuseCountDown;

        if (plantedC4.defuserHandle == GameData::local().handle) {
            if (canDefuse) {
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
                ImGui::textUnformattedCentered("You can defuse!");
            }
            else {
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
                ImGui::textUnformattedCentered("You can not defuse!");
            }
            ImGui::PopStyleColor();
        }
        else if (const auto defusingPlayer = GameData::playerByHandle(plantedC4.defuserHandle)) {
            std::ostringstream ss; ss << defusingPlayer->name << " is defusing: " << std::fixed << std::showpoint << std::setprecision(3) << (std::max)(plantedC4.defuseCountDown - memory->globalVars->currenttime, 0.0f) << " s";

            ImGui::textUnformattedCentered(ss.str().c_str());

            ImGui::PushStyleColor(ImGuiCol_PlotHistogram, canDefuse ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 0, 0, 255));
            ImGui::progressBarFullWidth((plantedC4.defuseCountDown - memory->globalVars->currenttime) / plantedC4.defuseLength, 5.0f);
            ImGui::PopStyleColor();
        }
    }

    windowWidth = ImGui::GetCurrentWindow()->SizeFull.x;

    ImGui::PopStyleColor(2);
    ImGui::End();
}

void Misc::stealNames() noexcept
{
    if (!miscConfig.nameStealer)
        return;

    if (!localPlayer)
        return;

    static std::vector<int> stolenIds;

    for (int i = 1; i <= memory->globalVars->maxClients; ++i) {
        const auto entity = interfaces->entityList->getEntity(i);

        if (!entity || entity == localPlayer.get())
            continue;

        PlayerInfo playerInfo;
        if (!interfaces->engine->getPlayerInfo(entity->index(), playerInfo))
            continue;

        if (playerInfo.fakeplayer || std::ranges::find(stolenIds, playerInfo.userId) != stolenIds.cend())
            continue;

        if (changeName(false, (std::string{ playerInfo.name } + '\x1').c_str(), 1.0f))
            stolenIds.push_back(playerInfo.userId);

        return;
    }
    stolenIds.clear();
}

void Misc::disablePanoramablur() noexcept
{
    static auto blur = interfaces->cvar->findVar("@panorama_disable_blur");
    blur->setValue(miscConfig.disablePanoramablur);
}

void Misc::quickReload(UserCmd* cmd) noexcept
{
    if (miscConfig.quickReload) {
        static Entity* reloadedWeapon{ nullptr };

        if (reloadedWeapon) {
            for (auto weaponHandle : localPlayer->weapons()) {
                if (weaponHandle == -1)
                    break;

                if (interfaces->entityList->getEntityFromHandle(weaponHandle) == reloadedWeapon) {
                    cmd->weaponselect = reloadedWeapon->index();
                    cmd->weaponsubtype = reloadedWeapon->getWeaponSubType();
                    break;
                }
            }
            reloadedWeapon = nullptr;
        }

        if (auto activeWeapon{ localPlayer->getActiveWeapon() }; activeWeapon && activeWeapon->isInReload() && activeWeapon->clip() == activeWeapon->getWeaponData()->maxClip) {
            reloadedWeapon = activeWeapon;

            for (auto weaponHandle : localPlayer->weapons()) {
                if (weaponHandle == -1)
                    break;

                if (auto weapon{ interfaces->entityList->getEntityFromHandle(weaponHandle) }; weapon && weapon != reloadedWeapon) {
                    cmd->weaponselect = weapon->index();
                    cmd->weaponsubtype = weapon->getWeaponSubType();
                    break;
                }
            }
        }
    }
}

bool Misc::changeName(bool reconnect, const char* newName, float delay) noexcept
{
    static auto exploitInitialized{ false };

    static auto name{ interfaces->cvar->findVar("name") };

    if (reconnect) {
        exploitInitialized = false;
        return false;
    }

    if (!exploitInitialized && interfaces->engine->isInGame()) {
        if (PlayerInfo playerInfo; localPlayer && interfaces->engine->getPlayerInfo(localPlayer->index(), playerInfo) && (!strcmp(playerInfo.name, "?empty") || !strcmp(playerInfo.name, "\n\xAD\xAD\xAD"))) {
            exploitInitialized = true;
        }
        else {
            name->onChangeCallbacks.size = 0;
            name->setValue("\n\xAD\xAD\xAD");
            return false;
        }
    }

    if (static auto nextChangeTime = 0.0f; nextChangeTime <= memory->globalVars->realtime) {
        name->setValue(newName);
        nextChangeTime = memory->globalVars->realtime + delay;
        return true;
    }
    return false;
}

void Misc::bunnyHop(UserCmd* cmd) noexcept
{
    if (!localPlayer)
        return;

    static auto wasLastTimeOnGround{ localPlayer->flags() & 1 };

    if (miscConfig.bunnyHop && !(localPlayer->flags() & 1) && localPlayer->moveType() != MoveType::LADDER && !wasLastTimeOnGround)
        cmd->buttons &= ~UserCmd::IN_JUMP;

    wasLastTimeOnGround = localPlayer->flags() & 1;
}

void Misc::fakeBan(bool set) noexcept
{
    static bool shouldSet = false;

    if (set)
        shouldSet = set;

    if (shouldSet && interfaces->engine->isInGame() && changeName(false, std::string{ "\x1\xB" }.append(std::string{ static_cast<char>(miscConfig.banColor + 1) }).append(miscConfig.banText).append("\x1").c_str(), 5.0f))
        shouldSet = false;
}

void Misc::nadePredict() noexcept
{
    static auto nadeVar{ interfaces->cvar->findVar("cl_grenadepreview") };

    nadeVar->onChangeCallbacks.size = 0;
    nadeVar->setValue(miscConfig.nadePredict);
}

void Misc::fixTabletSignal() noexcept
{
    if (miscConfig.fixTabletSignal && localPlayer) {
        if (auto activeWeapon{ localPlayer->getActiveWeapon() }; activeWeapon && activeWeapon->getClientClass()->classId == ClassId::Tablet)
            activeWeapon->tabletReceptionIsBlocked() = false;
    }
}

void Misc::killMessage(GameEvent& event) noexcept
{
    if (!miscConfig.killMessage)
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    if (const auto localUserId = localPlayer->getUserId(); event.getInt("attacker") != localUserId || event.getInt("userid") == localUserId)
        return;

    std::string cmd = "say \"";
    cmd += miscConfig.killMessageString;
    cmd += '"';
    interfaces->engine->clientCmdUnrestricted(cmd.c_str());
}

void Misc::fixMovement(UserCmd* cmd, float yaw) noexcept
{
    if (miscConfig.fixMovement) {
        float oldYaw = yaw + (yaw < 0.0f ? 360.0f : 0.0f);
        float newYaw = cmd->viewangles.y + (cmd->viewangles.y < 0.0f ? 360.0f : 0.0f);
        float yawDelta = newYaw < oldYaw ? fabsf(newYaw - oldYaw) : 360.0f - fabsf(newYaw - oldYaw);
        yawDelta = 360.0f - yawDelta;

        const float forwardmove = cmd->forwardmove;
        const float sidemove = cmd->sidemove;
        cmd->forwardmove = std::cos(Helpers::deg2rad(yawDelta)) * forwardmove + std::cos(Helpers::deg2rad(yawDelta + 90.0f)) * sidemove;
        cmd->sidemove = std::sin(Helpers::deg2rad(yawDelta)) * forwardmove + std::sin(Helpers::deg2rad(yawDelta + 90.0f)) * sidemove;
    }
}

void Misc::antiAfkKick(UserCmd* cmd) noexcept
{
    if (miscConfig.antiAfkKick && cmd->commandNumber % 2)
        cmd->buttons |= 1 << 26;
}

void Misc::fixAnimationLOD(FrameStage stage) noexcept
{
#ifdef _WIN32
    if (miscConfig.fixAnimationLOD && stage == FrameStage::RENDER_START) {
        if (!localPlayer)
            return;

        for (int i = 1; i <= interfaces->engine->getMaxClients(); i++) {
            Entity* entity = interfaces->entityList->getEntity(i);
            if (!entity || entity == localPlayer.get() || entity->isDormant() || !entity->isAlive()) continue;
            *reinterpret_cast<int*>(entity + 0xA28) = 0;
            *reinterpret_cast<int*>(entity + 0xA30) = memory->globalVars->framecount;
        }
    }
#endif
}

void Misc::autoPistol(UserCmd* cmd) noexcept
{
    if (miscConfig.autoPistol && localPlayer) {
        const auto activeWeapon = localPlayer->getActiveWeapon();
        if (activeWeapon && activeWeapon->isPistol() && activeWeapon->nextPrimaryAttack() > memory->globalVars->serverTime()) {
            if (activeWeapon->itemDefinitionIndex() == WeaponId::Revolver)
                cmd->buttons &= ~UserCmd::IN_ATTACK2;
            else
                cmd->buttons &= ~UserCmd::IN_ATTACK;
        }
    }
}

void Misc::chokePackets(bool& sendPacket) noexcept
{
    if (!miscConfig.chokedPacketsKey.isSet() || miscConfig.chokedPacketsKey.isDown())
        sendPacket = interfaces->engine->getNetworkChannel()->chokedPackets >= miscConfig.chokedPackets;
}

void Misc::autoReload(UserCmd* cmd) noexcept
{
    if (miscConfig.autoReload && localPlayer) {
        const auto activeWeapon = localPlayer->getActiveWeapon();
        if (activeWeapon && getWeaponIndex(activeWeapon->itemDefinitionIndex()) && !activeWeapon->clip())
            cmd->buttons &= ~(UserCmd::IN_ATTACK | UserCmd::IN_ATTACK2);
    }
}

void Misc::revealRanks(UserCmd* cmd) noexcept
{
    if (miscConfig.revealRanks && cmd->buttons & UserCmd::IN_SCORE)
        interfaces->client->dispatchUserMessage(50, 0, 0, nullptr);
}

void Misc::autoStrafe(UserCmd* cmd) noexcept
{
    if (localPlayer
        && miscConfig.autoStrafe
        && !(localPlayer->flags() & 1)
        && localPlayer->moveType() != MoveType::NOCLIP) {
        if (cmd->mousedx < 0)
            cmd->sidemove = -450.0f;
        else if (cmd->mousedx > 0)
            cmd->sidemove = 450.0f;
    }
}

void Misc::removeCrouchCooldown(UserCmd* cmd) noexcept
{
    if (miscConfig.fastDuck)
        cmd->buttons |= UserCmd::IN_BULLRUSH;
}

void Misc::moonwalk(UserCmd* cmd) noexcept
{
    if (miscConfig.moonwalk && localPlayer && localPlayer->moveType() != MoveType::LADDER)
        cmd->buttons ^= UserCmd::IN_FORWARD | UserCmd::IN_BACK | UserCmd::IN_MOVELEFT | UserCmd::IN_MOVERIGHT;
}

void Misc::playHitSound(GameEvent& event) noexcept
{
    if (!miscConfig.hitSound)
        return;

    if (!localPlayer)
        return;

    if (const auto localUserId = localPlayer->getUserId(); event.getInt("attacker") != localUserId || event.getInt("userid") == localUserId)
        return;

    constexpr std::array hitSounds{
        "play physics/metal/metal_solid_impact_bullet2",
        "play buttons/arena_switch_press_02",
        "play training/timer_bell",
        "play physics/glass/glass_impact_bullet1"
    };

    if (static_cast<std::size_t>(miscConfig.hitSound - 1) < hitSounds.size())
        interfaces->engine->clientCmdUnrestricted(hitSounds[miscConfig.hitSound - 1]);
    else if (miscConfig.hitSound == 5)
        interfaces->engine->clientCmdUnrestricted(("play " + miscConfig.customHitSound).c_str());
}

void Misc::killSound(GameEvent& event) noexcept
{
    if (!miscConfig.killSound)
        return;

    if (!localPlayer || !localPlayer->isAlive())
        return;

    if (const auto localUserId = localPlayer->getUserId(); event.getInt("attacker") != localUserId || event.getInt("userid") == localUserId)
        return;

    constexpr std::array killSounds{
        "play physics/metal/metal_solid_impact_bullet2",
        "play buttons/arena_switch_press_02",
        "play training/timer_bell",
        "play physics/glass/glass_impact_bullet1"
    };

    if (static_cast<std::size_t>(miscConfig.killSound - 1) < killSounds.size())
        interfaces->engine->clientCmdUnrestricted(killSounds[miscConfig.killSound - 1]);
    else if (miscConfig.killSound == 5)
        interfaces->engine->clientCmdUnrestricted(("play " + miscConfig.customKillSound).c_str());
}

void Misc::purchaseList(GameEvent* event) noexcept
{
    static std::mutex mtx;
    std::scoped_lock _{ mtx };

    struct PlayerPurchases {
        int totalCost;
        std::unordered_map<std::string, int> items;
    };

    static std::unordered_map<int, PlayerPurchases> playerPurchases;
    static std::unordered_map<std::string, int> purchaseTotal;
    static int totalCost;

    static auto freezeEnd = 0.0f;

    if (event) {
        switch (fnv::hashRuntime(event->getName())) {
        case fnv::hash("item_purchase"): {
            if (const auto player = interfaces->entityList->getEntity(interfaces->engine->getPlayerForUserID(event->getInt("userid"))); player && localPlayer && localPlayer->isOtherEnemy(player)) {
                if (const auto definition = memory->itemSystem()->getItemSchema()->getItemDefinitionByName(event->getString("weapon"))) {
                    auto& purchase = playerPurchases[player->handle()];
                    if (const auto weaponInfo = memory->weaponSystem->getWeaponInfo(definition->getWeaponId())) {
                        purchase.totalCost += weaponInfo->price;
                        totalCost += weaponInfo->price;
                    }
                    const std::string weapon = interfaces->localize->findAsUTF8(definition->getItemBaseName());
                    ++purchaseTotal[weapon];
                    ++purchase.items[weapon];
                }
            }
            break;
        }
        case fnv::hash("round_start"):
            freezeEnd = 0.0f;
            playerPurchases.clear();
            purchaseTotal.clear();
            totalCost = 0;
            break;
        case fnv::hash("round_freeze_end"):
            freezeEnd = memory->globalVars->realtime;
            break;
        }
    }
    else {
        if (!miscConfig.purchaseList.enabled)
            return;

        if (static const auto mp_buytime = interfaces->cvar->findVar("mp_buytime"); (!interfaces->engine->isInGame() || freezeEnd != 0.0f && memory->globalVars->realtime > freezeEnd + (!miscConfig.purchaseList.onlyDuringFreezeTime ? mp_buytime->getFloat() : 0.0f) || playerPurchases.empty() || purchaseTotal.empty()) && !gui->isOpen())
            return;

        ImGui::SetNextWindowSize({ 200.0f, 200.0f }, ImGuiCond_Once);

        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;
        if (!gui->isOpen())
            windowFlags |= ImGuiWindowFlags_NoInputs;
        if (miscConfig.purchaseList.noTitleBar)
            windowFlags |= ImGuiWindowFlags_NoTitleBar;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, { 0.5f, 0.5f });
        ImGui::Begin("Purchases", nullptr, windowFlags);
        ImGui::PopStyleVar();

        if (miscConfig.purchaseList.mode == PurchaseList::Details) {
            GameData::Lock lock;

            for (const auto& [handle, purchases] : playerPurchases) {
                std::string s;
                s.reserve(std::accumulate(purchases.items.begin(), purchases.items.end(), 0, [](int length, const auto& p) { return length + p.first.length() + 2; }));
                for (const auto& purchasedItem : purchases.items) {
                    if (purchasedItem.second > 1)
                        s += std::to_string(purchasedItem.second) + "x ";
                    s += purchasedItem.first + ", ";
                }

                if (s.length() >= 2)
                    s.erase(s.length() - 2);

                if (const auto player = GameData::playerByHandle(handle)) {
                    if (miscConfig.purchaseList.showPrices)
                        ImGui::TextWrapped("%s $%d: %s", player->name.c_str(), purchases.totalCost, s.c_str());
                    else
                        ImGui::TextWrapped("%s: %s", player->name.c_str(), s.c_str());
                }
            }
        }
        else if (miscConfig.purchaseList.mode == PurchaseList::Summary) {
            for (const auto& purchase : purchaseTotal)
                ImGui::TextWrapped("%d x %s", purchase.second, purchase.first.c_str());

            if (miscConfig.purchaseList.showPrices && totalCost > 0) {
                ImGui::Separator();
                ImGui::TextWrapped("Total: $%d", totalCost);
            }
        }
        ImGui::End();
    }
}

void Misc::oppositeHandKnife(FrameStage stage) noexcept
{
    if (!miscConfig.oppositeHandKnife)
        return;

    if (!localPlayer)
        return;

    if (stage != FrameStage::RENDER_START && stage != FrameStage::RENDER_END)
        return;

    static const auto cl_righthand = interfaces->cvar->findVar("cl_righthand");
    static bool original;

    if (stage == FrameStage::RENDER_START) {
        original = cl_righthand->getInt();

        if (const auto activeWeapon = localPlayer->getActiveWeapon()) {
            if (const auto classId = activeWeapon->getClientClass()->classId; classId == ClassId::Knife || classId == ClassId::KnifeGG)
                cl_righthand->setValue(!original);
        }
    }
    else {
        cl_righthand->setValue(original);
    }
}

static std::vector<std::uint64_t> reportedPlayers;
static int reportbotRound;

void Misc::runReportbot() noexcept
{
    if (!miscConfig.reportbot.enabled)
        return;

    if (!localPlayer)
        return;

    static auto lastReportTime = 0.0f;

    if (lastReportTime + miscConfig.reportbot.delay > memory->globalVars->realtime)
        return;

    if (reportbotRound >= miscConfig.reportbot.rounds)
        return;

    for (int i = 1; i <= interfaces->engine->getMaxClients(); ++i) {
        const auto entity = interfaces->entityList->getEntity(i);

        if (!entity || entity == localPlayer.get())
            continue;

        if (miscConfig.reportbot.target != 2 && (localPlayer->isOtherEnemy(entity) ? miscConfig.reportbot.target != 0 : miscConfig.reportbot.target != 1))
            continue;

        PlayerInfo playerInfo;
        if (!interfaces->engine->getPlayerInfo(i, playerInfo))
            continue;

        if (playerInfo.fakeplayer || std::ranges::find(reportedPlayers, playerInfo.xuid) != reportedPlayers.cend())
            continue;

        std::string report;

        if (miscConfig.reportbot.textAbuse)
            report += "textabuse,";
        if (miscConfig.reportbot.griefing)
            report += "grief,";
        if (miscConfig.reportbot.wallhack)
            report += "wallhack,";
        if (miscConfig.reportbot.aimbot)
            report += "aimbot,";
        if (miscConfig.reportbot.other)
            report += "speedhack,";

        if (!report.empty()) {
            memory->submitReport(std::to_string(playerInfo.xuid).c_str(), report.c_str());
            lastReportTime = memory->globalVars->realtime;
            reportedPlayers.push_back(playerInfo.xuid);
        }
        return;
    }

    reportedPlayers.clear();
    ++reportbotRound;
}

void Misc::resetReportbot() noexcept
{
    reportbotRound = 0;
    reportedPlayers.clear();
}

void Misc::preserveKillfeed(bool roundStart) noexcept
{
    if (!miscConfig.preserveKillfeed.enabled)
        return;

    static auto nextUpdate = 0.0f;

    if (roundStart) {
        nextUpdate = memory->globalVars->realtime + 10.0f;
        return;
    }

    if (nextUpdate > memory->globalVars->realtime)
        return;

    nextUpdate = memory->globalVars->realtime + 2.0f;

    const auto deathNotice = std::uintptr_t(memory->findHudElement(memory->hud, "CCSGO_HudDeathNotice"));
    if (!deathNotice)
        return;

    const auto deathNoticePanel = (*(UIPanel**)(*reinterpret_cast<std::uintptr_t*>(deathNotice WIN32_LINUX(-20 + 88, -32 + 128)) + sizeof(std::uintptr_t)));

    const auto childPanelCount = deathNoticePanel->getChildCount();

    for (int i = 0; i < childPanelCount; ++i) {
        const auto child = deathNoticePanel->getChild(i);
        if (!child)
            continue;

        if (child->hasClass("DeathNotice_Killer") && (!miscConfig.preserveKillfeed.onlyHeadshots || child->hasClass("DeathNoticeHeadShot")))
            child->setAttributeFloat("SpawnTime", memory->globalVars->currenttime);
    }
}

void Misc::voteRevealer(GameEvent& event) noexcept
{
    if (!miscConfig.revealVotes)
        return;

    const auto entity = interfaces->entityList->getEntity(event.getInt("entityid"));
    if (!entity || !entity->isPlayer())
        return;

    const auto votedYes = event.getInt("vote_option") == 0;
    const auto isLocal = localPlayer && entity == localPlayer.get();
    const char color = votedYes ? '\x06' : '\x07';

    memory->clientMode->getHudChat()->printf(0, " \x0C\u2022benzoboyz.net<3\u2022 %c%s\x01 voted %c%s\x01", isLocal ? '\x01' : color, isLocal ? "You" : entity->getPlayerName().c_str(), color, votedYes ? "Yes" : "No");
}

void Misc::onVoteStart(const void* data, int size) noexcept
{
    if (!miscConfig.revealVotes)
        return;

    constexpr auto voteName = [](int index) {
        switch (index) {
        case 0: return "Kick";
        case 1: return "Change Level";
        case 6: return "Surrender";
        case 13: return "Start TimeOut";
        default: return "";
        }
    };

    const auto reader = ProtobufReader{ static_cast<const std::uint8_t*>(data), size };
    const auto entityIndex = reader.readInt32(2);

    const auto entity = interfaces->entityList->getEntity(entityIndex);
    if (!entity || !entity->isPlayer())
        return;

    const auto isLocal = localPlayer && entity == localPlayer.get();

    const auto voteType = reader.readInt32(3);
    memory->clientMode->getHudChat()->printf(0, " \x0C\u2022benzoboyz.net<3\u2022 %c%s\x01 call vote (\x06%s\x01)", isLocal ? '\x01' : '\x06', isLocal ? "You" : entity->getPlayerName().c_str(), voteName(voteType));
}

void Misc::onVotePass() noexcept
{
    if (miscConfig.revealVotes)
        memory->clientMode->getHudChat()->printf(0, " \x0C\u2022benzoboyz.net<3\u2022\x01 Vote\x06 PASSED");
}

void Misc::onVoteFailed() noexcept
{
    if (miscConfig.revealVotes)
        memory->clientMode->getHudChat()->printf(0, " \x0C\u2022benzoboyz.net<3\u2022\x01 Vote\x07 FAILED");
}

// ImGui::ShadeVertsLinearColorGradientKeepAlpha() modified to do interpolation in HSV
static void shadeVertsHSVColorGradientKeepAlpha(ImDrawList* draw_list, int vert_start_idx, int vert_end_idx, ImVec2 gradient_p0, ImVec2 gradient_p1, ImU32 col0, ImU32 col1)
{
    ImVec2 gradient_extent = gradient_p1 - gradient_p0;
    float gradient_inv_length2 = 1.0f / ImLengthSqr(gradient_extent);
    ImDrawVert* vert_start = draw_list->VtxBuffer.Data + vert_start_idx;
    ImDrawVert* vert_end = draw_list->VtxBuffer.Data + vert_end_idx;

    ImVec4 col0HSV = ImGui::ColorConvertU32ToFloat4(col0);
    ImVec4 col1HSV = ImGui::ColorConvertU32ToFloat4(col1);
    ImGui::ColorConvertRGBtoHSV(col0HSV.x, col0HSV.y, col0HSV.z, col0HSV.x, col0HSV.y, col0HSV.z);
    ImGui::ColorConvertRGBtoHSV(col1HSV.x, col1HSV.y, col1HSV.z, col1HSV.x, col1HSV.y, col1HSV.z);
    ImVec4 colDelta = col1HSV - col0HSV;

    for (ImDrawVert* vert = vert_start; vert < vert_end; vert++)
    {
        float d = ImDot(vert->pos - gradient_p0, gradient_extent);
        float t = ImClamp(d * gradient_inv_length2, 0.0f, 1.0f);

        float h = col0HSV.x + colDelta.x * t;
        float s = col0HSV.y + colDelta.y * t;
        float v = col0HSV.z + colDelta.z * t;

        ImVec4 rgb;
        ImGui::ColorConvertHSVtoRGB(h, s, v, rgb.x, rgb.y, rgb.z);
        vert->col = (ImGui::ColorConvertFloat4ToU32(rgb) & ~IM_COL32_A_MASK) | (vert->col & IM_COL32_A_MASK);
    }
}

void Misc::drawOffscreenEnemies(ImDrawList* drawList) noexcept
{
    if (!miscConfig.offscreenEnemies.enabled)
        return;

    const auto yaw = Helpers::deg2rad(interfaces->engine->getViewAngles().y);

    GameData::Lock lock;
    for (auto& player : GameData::players()) {
        if ((player.dormant && player.fadingAlpha() == 0.0f) || !player.alive || !player.enemy || player.inViewFrustum)
            continue;

        const auto positionDiff = GameData::local().origin - player.origin;

        auto x = std::cos(yaw) * positionDiff.y - std::sin(yaw) * positionDiff.x;
        auto y = std::cos(yaw) * positionDiff.x + std::sin(yaw) * positionDiff.y;
        if (const auto len = std::sqrt(x * x + y * y); len != 0.0f) {
            x /= len;
            y /= len;
        }

        constexpr auto avatarRadius = 13.0f;
        constexpr auto triangleSize = 10.0f;

        const auto pos = ImGui::GetIO().DisplaySize / 2 + ImVec2{ x, y } *200;
        const auto trianglePos = pos + ImVec2{ x, y } *(avatarRadius + (miscConfig.offscreenEnemies.healthBar.enabled ? 5 : 3));

        Helpers::setAlphaFactor(player.fadingAlpha());
        const auto white = Helpers::calculateColor(255, 255, 255, 255);
        const auto background = Helpers::calculateColor(0, 0, 0, 80);
        const auto color = Helpers::calculateColor(miscConfig.offscreenEnemies.asColor4());
        const auto healthBarColor = miscConfig.offscreenEnemies.healthBar.type == HealthBar::HealthBased ? Helpers::healthColor(std::clamp(player.health / 100.0f, 0.0f, 1.0f)) : Helpers::calculateColor(miscConfig.offscreenEnemies.healthBar.asColor4());
        Helpers::setAlphaFactor(1.0f);

        const ImVec2 trianglePoints[]{
            trianglePos + ImVec2{  0.4f * y, -0.4f * x } *triangleSize,
            trianglePos + ImVec2{  1.0f * x,  1.0f * y } *triangleSize,
            trianglePos + ImVec2{ -0.4f * y,  0.4f * x } *triangleSize
        };

        drawList->AddConvexPolyFilled(trianglePoints, 3, color);
        drawList->AddCircleFilled(pos, avatarRadius + 1, white & IM_COL32_A_MASK, 40);

        const auto texture = player.getAvatarTexture();

        const bool pushTextureId = drawList->_TextureIdStack.empty() || texture != drawList->_TextureIdStack.back();
        if (pushTextureId)
            drawList->PushTextureID(texture);

        const int vertStartIdx = drawList->VtxBuffer.Size;
        drawList->AddCircleFilled(pos, avatarRadius, white, 40);
        const int vertEndIdx = drawList->VtxBuffer.Size;
        ImGui::ShadeVertsLinearUV(drawList, vertStartIdx, vertEndIdx, pos - ImVec2{ avatarRadius, avatarRadius }, pos + ImVec2{ avatarRadius, avatarRadius }, { 0, 0 }, { 1, 1 }, true);

        if (pushTextureId)
            drawList->PopTextureID();

        if (miscConfig.offscreenEnemies.healthBar.enabled) {
            const auto radius = avatarRadius + 2;
            const auto healthFraction = std::clamp(player.health / 100.0f, 0.0f, 1.0f);

            drawList->AddCircle(pos, radius, background, 40, 3.0f);

            const int vertStartIdx = drawList->VtxBuffer.Size;
            if (healthFraction == 1.0f) { // sometimes PathArcTo is missing one top pixel when drawing a full circle, so draw it with AddCircle
                drawList->AddCircle(pos, radius, healthBarColor, 40, 2.0f);
            }
            else {
                constexpr float pi = std::numbers::pi_v<float>;
                drawList->PathArcTo(pos, radius - 0.5f, pi / 2 - pi * healthFraction, pi / 2 + pi * healthFraction, 40);
                drawList->PathStroke(healthBarColor, false, 2.0f);
            }
            const int vertEndIdx = drawList->VtxBuffer.Size;

            if (miscConfig.offscreenEnemies.healthBar.type == HealthBar::Gradient)
                shadeVertsHSVColorGradientKeepAlpha(drawList, vertStartIdx, vertEndIdx, pos - ImVec2{ 0.0f, radius }, pos + ImVec2{ 0.0f, radius }, IM_COL32(0, 255, 0, 255), IM_COL32(255, 0, 0, 255));
        }
    }
}

void Misc::autoAccept(const char* soundEntry) noexcept
{
    if (!miscConfig.autoAccept)
        return;

    if (std::strcmp(soundEntry, "UIPanorama.popup_accept_match_beep"))
        return;

    if (const auto idx = memory->registeredPanoramaEvents->find(memory->makePanoramaSymbol("MatchAssistedAccept")); idx != -1) {
        if (const auto eventPtr = memory->registeredPanoramaEvents->memory[idx].value.makeEvent(nullptr))
            interfaces->panoramaUIEngine->accessUIEngine()->dispatchEvent(eventPtr);
    }

#ifdef _WIN32
    auto window = FindWindowW(L"Valve001", NULL);
    FLASHWINFO flash{ sizeof(FLASHWINFO), window, FLASHW_TRAY | FLASHW_TIMERNOFG, 0, 0 };
    FlashWindowEx(&flash);
    ShowWindow(window, SW_RESTORE);
#endif
}

void Misc::updateEventListeners(bool forceRemove) noexcept
{
    class PurchaseEventListener : public GameEventListener {
    public:
        void fireGameEvent(GameEvent* event) override { purchaseList(event); }
    };

    static PurchaseEventListener listener;
    static bool listenerRegistered = false;

    if (miscConfig.purchaseList.enabled && !listenerRegistered) {
        interfaces->gameEventManager->addListener(&listener, "item_purchase");
        listenerRegistered = true;
    }
    else if ((!miscConfig.purchaseList.enabled || forceRemove) && listenerRegistered) {
        interfaces->gameEventManager->removeListener(&listener);
        listenerRegistered = false;
    }
}

void Misc::updateInput() noexcept
{

}




static void from_json(const json& j, ImVec2& v)
{
    read(j, "X", v.x);
    read(j, "Y", v.y);
}

static void from_json(const json& j, PurchaseList& pl)
{
    read(j, "Enabled", pl.enabled);
    read(j, "Only During Freeze Time", pl.onlyDuringFreezeTime);
    read(j, "Show Prices", pl.showPrices);
    read(j, "No Title Bar", pl.noTitleBar);
    read(j, "Mode", pl.mode);
}

static void from_json(const json& j, OffscreenEnemies& o)
{
    from_json(j, static_cast<ColorToggle&>(o));

    read<value_t::object>(j, "Health Bar", o.healthBar);
}

static void from_json(const json& j, MiscConfig::SpectatorList& sl)
{
    read(j, "Enabled", sl.enabled);
    read(j, "No Title Bar", sl.noTitleBar);
    read<value_t::object>(j, "Pos", sl.pos);
    read<value_t::object>(j, "Size", sl.size);
}

static void from_json(const json& j, MiscConfig::Watermark& o)
{
    read(j, "Enabled", o.enabled);
}

static void from_json(const json& j, PreserveKillfeed& o)
{
    read(j, "Enabled", o.enabled);
    read(j, "Only Headshots", o.onlyHeadshots);
}

static void from_json(const json& j, MiscConfig& m)
{
    read(j, "Menu key", m.menuKey);
    read(j, "Anti AFK kick", m.antiAfkKick);
    read(j, "Auto strafe", m.autoStrafe);
    read(j, "Bunny hop", m.bunnyHop);
    read(j, "Custom clan tag", m.customClanTag);
    read(j, "Clock tag", m.clocktag);
    read(j, "Clan tag", m.clanTag, sizeof(m.clanTag));
    read(j, "Animated clan tag", m.animatedClanTag);
    read(j, "Fast duck", m.fastDuck);
    read(j, "Moonwalk", m.moonwalk);
    read(j, "Edge Jump", m.edgejump);
    read(j, "Edge Jump Key", m.edgejumpkey);
    read(j, "Slowwalk", m.slowwalk);
    read(j, "Slowwalk key", m.slowwalkKey);
    read<value_t::object>(j, "Noscope crosshair", m.noscopeCrosshair);
    read<value_t::object>(j, "Recoil crosshair", m.recoilCrosshair);
    read(j, "Auto pistol", m.autoPistol);
    read(j, "Auto reload", m.autoReload);
    read(j, "Auto accept", m.autoAccept);
    read(j, "Radar hack", m.radarHack);
    read(j, "Reveal ranks", m.revealRanks);
    read(j, "Reveal money", m.revealMoney);
    read(j, "Reveal suspect", m.revealSuspect);
    read(j, "Reveal votes", m.revealVotes);
    read<value_t::object>(j, "Spectator list", m.spectatorList);
    read<value_t::object>(j, "Watermark", m.watermark);
    read<value_t::object>(j, "Offscreen Enemies", m.offscreenEnemies);
    read(j, "Fix animation LOD", m.fixAnimationLOD);
    read(j, "Fix bone matrix", m.fixBoneMatrix);
    read(j, "Fix movement", m.fixMovement);
    read(j, "Disable model occlusion", m.disableModelOcclusion);
    read(j, "Aspect Ratio", m.aspectratio);
    read(j, "Kill message", m.killMessage);
    read<value_t::string>(j, "Kill message string", m.killMessageString);
    read(j, "Name stealer", m.nameStealer);
    read(j, "Disable HUD blur", m.disablePanoramablur);
    read(j, "Ban color", m.banColor);
    read<value_t::string>(j, "Ban text", m.banText);
    read(j, "Fast plant", m.fastPlant);
    read(j, "Fast Stop", m.fastStop);
    read<value_t::object>(j, "Bomb timer", m.bombTimer);
    read(j, "Quick reload", m.quickReload);
    read(j, "Prepare revolver", m.prepareRevolver);
    read(j, "Prepare revolver key", m.prepareRevolverKey);
    read(j, "Hit sound", m.hitSound);
    read(j, "Choked packets", m.chokedPackets);
    read(j, "Choked packets key", m.chokedPacketsKey);
    read(j, "Quick healthshot key", m.quickHealthshotKey);
    read(j, "Grenade predict", m.nadePredict);
    read(j, "Fix tablet signal", m.fixTabletSignal);
    read(j, "Max angle delta", m.maxAngleDelta);
    read(j, "Fix tablet signal", m.fixTabletSignal);
    read<value_t::string>(j, "Custom Hit Sound", m.customHitSound);
    read(j, "Kill sound", m.killSound);
    read<value_t::string>(j, "Custom Kill Sound", m.customKillSound);
    read<value_t::object>(j, "Purchase List", m.purchaseList);
    read<value_t::object>(j, "Reportbot", m.reportbot);
    read(j, "Opposite Hand Knife", m.oppositeHandKnife);
    read<value_t::object>(j, "Preserve Killfeed", m.preserveKillfeed);
}

static void from_json(const json& j, MiscConfig::Reportbot& r)
{
    read(j, "Enabled", r.enabled);
    read(j, "Target", r.target);
    read(j, "Delay", r.delay);
    read(j, "Rounds", r.rounds);
    read(j, "Abusive Communications", r.textAbuse);
    read(j, "Griefing", r.griefing);
    read(j, "Wall Hacking", r.wallhack);
    read(j, "Aim Hacking", r.aimbot);
    read(j, "Other Hacking", r.other);
}

static void to_json(json& j, const MiscConfig::Reportbot& o, const MiscConfig::Reportbot& dummy = {})
{
    WRITE("Enabled", enabled);
    WRITE("Target", target);
    WRITE("Delay", delay);
    WRITE("Rounds", rounds);
    WRITE("Abusive Communications", textAbuse);
    WRITE("Griefing", griefing);
    WRITE("Wall Hacking", wallhack);
    WRITE("Aim Hacking", aimbot);
    WRITE("Other Hacking", other);
}

static void to_json(json& j, const PurchaseList& o, const PurchaseList& dummy = {})
{
    WRITE("Enabled", enabled);
    WRITE("Only During Freeze Time", onlyDuringFreezeTime);
    WRITE("Show Prices", showPrices);
    WRITE("No Title Bar", noTitleBar);
    WRITE("Mode", mode);
}

static void to_json(json& j, const ImVec2& o, const ImVec2& dummy = {})
{
    WRITE("X", x);
    WRITE("Y", y);
}

static void to_json(json& j, const OffscreenEnemies& o, const OffscreenEnemies& dummy = {})
{
    to_json(j, static_cast<const ColorToggle&>(o), dummy);

    WRITE("Health Bar", healthBar);
}

static void to_json(json& j, const MiscConfig::SpectatorList& o, const MiscConfig::SpectatorList& dummy = {})
{
    WRITE("Enabled", enabled);
    WRITE("No Title Bar", noTitleBar);

    if (const auto window = ImGui::FindWindowByName("Spectator list")) {
        j["Pos"] = window->Pos;
        j["Size"] = window->SizeFull;
    }
}

static void to_json(json& j, const MiscConfig::Watermark& o, const MiscConfig::Watermark& dummy = {})
{
    WRITE("Enabled", enabled);
}

static void to_json(json& j, const PreserveKillfeed& o, const PreserveKillfeed& dummy = {})
{
    WRITE("Enabled", enabled);
    WRITE("Only Headshots", onlyHeadshots);
}

static void to_json(json& j, const MiscConfig& o)
{
    const MiscConfig dummy;

    WRITE("Menu key", menuKey);
    WRITE("Anti AFK kick", antiAfkKick);
    WRITE("Auto strafe", autoStrafe);
    WRITE("Bunny hop", bunnyHop);
    WRITE("Custom clan tag", customClanTag);
    WRITE("Clock tag", clocktag);

    if (o.clanTag[0])
        j["Clan tag"] = o.clanTag;

    WRITE("Animated clan tag", animatedClanTag);
    WRITE("Fast duck", fastDuck);
    WRITE("Moonwalk", moonwalk);
    WRITE("Edge Jump", edgejump);
    WRITE("Edge Jump Key", edgejumpkey);
    WRITE("Slowwalk", slowwalk);
    WRITE("Slowwalk key", slowwalkKey);
    WRITE("Noscope crosshair", noscopeCrosshair);
    WRITE("Recoil crosshair", recoilCrosshair);
    WRITE("Auto pistol", autoPistol);
    WRITE("Auto reload", autoReload);
    WRITE("Auto accept", autoAccept);
    WRITE("Radar hack", radarHack);
    WRITE("Reveal ranks", revealRanks);
    WRITE("Reveal money", revealMoney);
    WRITE("Reveal suspect", revealSuspect);
    WRITE("Reveal votes", revealVotes);
    WRITE("Spectator list", spectatorList);
    WRITE("Watermark", watermark);
    WRITE("Offscreen Enemies", offscreenEnemies);
    WRITE("Fix animation LOD", fixAnimationLOD);
    WRITE("Fix bone matrix", fixBoneMatrix);
    WRITE("Fix movement", fixMovement);
    WRITE("Disable model occlusion", disableModelOcclusion);
    WRITE("Aspect Ratio", aspectratio);
    WRITE("Kill message", killMessage);
    WRITE("Kill message string", killMessageString);
    WRITE("Name stealer", nameStealer);
    WRITE("Disable HUD blur", disablePanoramablur);
    WRITE("Ban color", banColor);
    WRITE("Ban text", banText);
    WRITE("Fast plant", fastPlant);
    WRITE("Fast Stop", fastStop);
    WRITE("Bomb timer", bombTimer);
    WRITE("Quick reload", quickReload);
    WRITE("Prepare revolver", prepareRevolver);
    WRITE("Prepare revolver key", prepareRevolverKey);
    WRITE("Hit sound", hitSound);
    WRITE("Choked packets", chokedPackets);
    WRITE("Choked packets key", chokedPacketsKey);
    WRITE("Quick healthshot key", quickHealthshotKey);
    WRITE("Grenade predict", nadePredict);
    WRITE("Fix tablet signal", fixTabletSignal);
    WRITE("Max angle delta", maxAngleDelta);
    WRITE("Fix tablet signal", fixTabletSignal);
    WRITE("Custom Hit Sound", customHitSound);
    WRITE("Kill sound", killSound);
    WRITE("Custom Kill Sound", customKillSound);
    WRITE("Purchase List", purchaseList);
    WRITE("Reportbot", reportbot);
    WRITE("Opposite Hand Knife", oppositeHandKnife);
    WRITE("Preserve Killfeed", preserveKillfeed);
}

json Misc::toJson() noexcept
{
    json j;
    to_json(j, miscConfig);
    return j;
}

void Misc::fromJson(const json& j) noexcept
{
    from_json(j, miscConfig);
}

void Misc::resetConfig() noexcept
{
    miscConfig = {};
}


#if OSIRIS_GLOW()

struct GlowItem : Color4 {
    bool enabled = false;
    bool healthBased = false;
    int style = 0;
};

struct PlayerGlow {
    GlowItem all, visible, occluded;
};



static std::unordered_map<std::string, PlayerGlow> playerGlowConfig;
static std::unordered_map<std::string, GlowItem> glowConfig;
static KeyBindToggle glowToggleKey;
static KeyBind glowHoldKey;

static std::vector<std::pair<int, int>> customGlowEntities;

void Glow::render() noexcept
{
    if (!localPlayer)
        return;

    auto& glow = glowConfig;

    Glow::clearCustomObjects();

    if (glowToggleKey.isSet()) {
        if (!glowToggleKey.isToggled() && !glowHoldKey.isDown())
            return;
    }
    else if (glowHoldKey.isSet() && !glowHoldKey.isDown()) {
        return;
    }

    for (int i = interfaces->engine->getMaxClients() + 1; i <= interfaces->entityList->getHighestEntityIndex(); ++i) {
        const auto entity = interfaces->entityList->getEntity(i);
        if (!entity || entity->isDormant())
            continue;

        switch (entity->getClientClass()->classId) {
        case ClassId::EconEntity:
        case ClassId::BaseCSGrenadeProjectile:
        case ClassId::BreachChargeProjectile:
        case ClassId::BumpMineProjectile:
        case ClassId::DecoyProjectile:
        case ClassId::MolotovProjectile:
        case ClassId::SensorGrenadeProjectile:
        case ClassId::SmokeGrenadeProjectile:
        case ClassId::SnowballProjectile:
        case ClassId::Hostage:
        case ClassId::CSRagdoll:
            if (!memory->glowObjectManager->hasGlowEffect(entity)) {
                if (auto index{ memory->glowObjectManager->registerGlowObject(entity) }; index != -1)
                    customGlowEntities.emplace_back(i, index);
            }
            break;
        default:
            break;
        }
    }

    for (int i = 0; i < memory->glowObjectManager->glowObjectDefinitions.size; i++) {
        GlowObjectDefinition& glowobject = memory->glowObjectManager->glowObjectDefinitions[i];

        auto entity = glowobject.entity;

        if (glowobject.isUnused() || !entity || entity->isDormant())
            continue;

        auto applyGlow = [&glowobject](const GlowItem& glow, int health = 0) noexcept
        {
            if (glow.enabled) {
                glowobject.renderWhenOccluded = true;
                glowobject.glowAlpha = glow.color[3];
                glowobject.glowStyle = glow.style;
                glowobject.glowAlphaMax = 0.6f;
                if (glow.healthBased && health) {
                    Helpers::healthColor(std::clamp(health / 100.0f, 0.0f, 1.0f), glowobject.glowColor.x, glowobject.glowColor.y, glowobject.glowColor.z);
                }
                else if (glow.rainbow) {
                    const auto [r, g, b] { rainbowColor(glow.rainbowSpeed) };
                    glowobject.glowColor = { r, g, b };
                }
                else {
                    glowobject.glowColor = { glow.color[0], glow.color[1], glow.color[2] };
                }
            }
        };

        auto applyPlayerGlow = [applyGlow](const std::string& name, Entity* entity) noexcept {
            const auto& cfg = playerGlowConfig[name];
            if (cfg.all.enabled)
                applyGlow(cfg.all, entity->health());
            else if (cfg.visible.enabled && entity->visibleTo(localPlayer.get()))
                applyGlow(cfg.visible, entity->health());
            else if (cfg.occluded.enabled && !entity->visibleTo(localPlayer.get()))
                applyGlow(cfg.occluded, entity->health());
        };

        switch (entity->getClientClass()->classId) {
        case ClassId::CSPlayer:
            if (!entity->isAlive())
                break;
            if (auto activeWeapon{ entity->getActiveWeapon() }; activeWeapon && activeWeapon->getClientClass()->classId == ClassId::C4 && activeWeapon->c4StartedArming())
                applyPlayerGlow("Planting", entity);
            else if (entity->isDefusing())
                applyPlayerGlow("Defusing", entity);
            else if (entity == localPlayer.get())
                applyGlow(glow["Local Player"], entity->health());
            else if (entity->isOtherEnemy(localPlayer.get()))
                applyPlayerGlow("Enemies", entity);
            else
                applyPlayerGlow("Allies", entity);
            break;
        case ClassId::C4: applyGlow(glow["C4"]); break;
        case ClassId::PlantedC4: applyGlow(glow["Planted C4"]); break;
        case ClassId::Chicken: applyGlow(glow["Chickens"]); break;
        case ClassId::EconEntity: applyGlow(glow["Defuse Kits"]); break;

        case ClassId::BaseCSGrenadeProjectile:
        case ClassId::BreachChargeProjectile:
        case ClassId::BumpMineProjectile:
        case ClassId::DecoyProjectile:
        case ClassId::MolotovProjectile:
        case ClassId::SensorGrenadeProjectile:
        case ClassId::SmokeGrenadeProjectile:
        case ClassId::SnowballProjectile:
            applyGlow(glow["Projectiles"]); break;

        case ClassId::Hostage: applyGlow(glow["Hostages"]); break;
        case ClassId::CSRagdoll: applyGlow(glow["Ragdolls"]); break;
        default:
            if (entity->isWeapon()) {
                applyGlow(glow["Weapons"]);
                if (!glow["Weapons"].enabled) glowobject.renderWhenOccluded = false;
            }
        }
    }
}

void Glow::clearCustomObjects() noexcept
{
    for (const auto& [entityIndex, glowObjectIndex] : customGlowEntities)
        memory->glowObjectManager->unregisterGlowObject(glowObjectIndex);

    customGlowEntities.clear();
}

void Glow::updateInput() noexcept
{
    glowToggleKey.handleToggle();
}

static bool glowWindowOpen = false;


static void to_json(json& j, const GlowItem& o, const GlowItem& dummy = {})
{
    to_json(j, static_cast<const Color4&>(o), dummy);
    WRITE("Enabled", enabled);
    WRITE("Health based", healthBased);
    WRITE("Style", style);
}

static void to_json(json& j, const PlayerGlow& o, const PlayerGlow& dummy = {})
{
    WRITE("All", all);
    WRITE("Visible", visible);
    WRITE("Occluded", occluded);
}

json Glow::toJson() noexcept
{
    json j;
    j["Items"] = glowConfig;
    j["Players"] = playerGlowConfig;
    to_json(j["Toggle Key"], glowToggleKey, {});
    to_json(j["Hold Key"], glowHoldKey, {});
    return j;
}

static void from_json(const json& j, GlowItem& g)
{
    from_json(j, static_cast<Color4&>(g));

    read(j, "Enabled", g.enabled);
    read(j, "Health based", g.healthBased);
    read(j, "Style", g.style);
}

static void from_json(const json& j, PlayerGlow& g)
{
    read<value_t::object>(j, "All", g.all);
    read<value_t::object>(j, "Visible", g.visible);
    read<value_t::object>(j, "Occluded", g.occluded);
}

void Glow::fromJson(const json& j) noexcept
{
    read(j, "Items", glowConfig);
    read(j, "Players", playerGlowConfig);
    read(j, "Toggle Key", glowToggleKey);
    read(j, "Hold Key", glowHoldKey);
}

void Glow::resetConfig() noexcept
{
    glowConfig = {};
    playerGlowConfig = {};
    glowToggleKey = {};
    glowHoldKey = {};
}

#else

void Glow::render() noexcept {}
void Glow::clearCustomObjects() noexcept {}
void Glow::updateInput() noexcept {}

// GUI

// Config
json Glow::toJson() noexcept { return {}; }
void Glow::fromJson(const json& j) noexcept {}
void Glow::resetConfig() noexcept {}

#endif

static void addToInventory(const std::unordered_map<StaticData::ItemIndex, int>& toAdd, const std::vector<StaticData::ItemIndex>& order) noexcept
{
    for (const auto item : order) {
        if (const auto count = toAdd.find(item); count != toAdd.end()) {
            for (int i = 0; i < count->second; ++i)
                Inventory::addItemUnacknowledged(item, Inventory::InvalidDynamicDataIdx);
        }
    }
}

static Entity* createGlove(int entry, int serial) noexcept
{
    static const auto createWearable = [] {
        std::add_pointer_t<Entity* __CDECL(int, int)> createWearableFn = nullptr;
        for (auto clientClass = interfaces->client->getAllClasses(); clientClass; clientClass = clientClass->next) {
            if (clientClass->classId == ClassId::EconWearable) {
                createWearableFn = clientClass->createFunction;
                break;
            }
        }
        return createWearableFn;
    }();

    if (!createWearable)
        return nullptr;

    if (const auto wearable = createWearable(entry, serial))
        return reinterpret_cast<Entity*>(std::uintptr_t(wearable) - 2 * sizeof(std::uintptr_t));
    return nullptr;
}

static void applyGloves(CSPlayerInventory& localInventory, Entity* local) noexcept
{
    const auto itemView = localInventory.getItemInLoadout(local->getTeamNumber(), 41);
    if (!itemView)
        return;

    const auto soc = memory->getSOCData(itemView);
    if (!soc)
        return;

    const auto item = Inventory::getItem(soc->itemID);
    if (!item || !item->isGlove())
        return;

    const auto wearables = local->wearables();
    static int gloveHandle = 0;

    auto glove = interfaces->entityList->getEntityFromHandle(wearables[0]);
    if (!glove)
        glove = interfaces->entityList->getEntityFromHandle(gloveHandle);

    constexpr auto NUM_ENT_ENTRIES = 8192;
    if (!glove)
        glove = createGlove(NUM_ENT_ENTRIES - 1, -1);

    if (!glove)
        return;

    wearables[0] = gloveHandle = glove->handle();
    glove->accountID() = localInventory.getAccountID();
    glove->entityQuality() = 3;
    local->body() = 1;

    bool dataUpdated = false;
    if (auto& definitionIndex = glove->itemDefinitionIndex(); definitionIndex != item->get().weaponID) {
        definitionIndex = item->get().weaponID;

        if (const auto def = memory->itemSystem()->getItemSchema()->getItemDefinitionInterface(item->get().weaponID))
            glove->setModelIndex(interfaces->modelInfo->getModelIndex(def->getWorldDisplayModel()));

        dataUpdated = true;
    }

    if (glove->itemID() != soc->itemID) {
        glove->itemIDHigh() = std::uint32_t(soc->itemID >> 32);
        glove->itemIDLow() = std::uint32_t(soc->itemID & 0xFFFFFFFF);
        dataUpdated = true;
    }

    glove->initialized() = true;
    memory->equipWearable(glove, local);

    if (dataUpdated) {
        // FIXME: This leaks memory
        glove->econItemView().visualDataProcessors().size = 0;
        glove->econItemView().customMaterials().size = 0;
        //

        glove->postDataUpdate(0);
        glove->onDataChanged(0);
    }
}

static void applyKnife(CSPlayerInventory& localInventory, Entity* local) noexcept
{
    const auto localXuid = local->getSteamId();

    const auto itemView = localInventory.getItemInLoadout(local->getTeamNumber(), 0);
    if (!itemView)
        return;

    const auto soc = memory->getSOCData(itemView);
    if (!soc)
        return;

    const auto item = Inventory::getItem(soc->itemID);
    if (!item || !item->isSkin())
        return;

    for (auto& weapons = local->weapons(); auto weaponHandle : weapons) {
        if (weaponHandle == -1)
            break;

        const auto weapon = interfaces->entityList->getEntityFromHandle(weaponHandle);
        if (!weapon)
            continue;

        auto& definitionIndex = weapon->itemDefinitionIndex();
        if (!Helpers::isKnife(definitionIndex))
            continue;

        if (weapon->originalOwnerXuid() != localXuid)
            continue;

        weapon->accountID() = localInventory.getAccountID();
        weapon->itemIDHigh() = std::uint32_t(soc->itemID >> 32);
        weapon->itemIDLow() = std::uint32_t(soc->itemID & 0xFFFFFFFF);
        weapon->entityQuality() = 3;

        if (definitionIndex != item->get().weaponID) {
            definitionIndex = item->get().weaponID;

            if (const auto def = memory->itemSystem()->getItemSchema()->getItemDefinitionInterface(item->get().weaponID)) {
                weapon->setModelIndex(interfaces->modelInfo->getModelIndex(def->getPlayerDisplayModel()));
                weapon->preDataUpdate(0);
            }
        }
    }

    const auto viewModel = interfaces->entityList->getEntityFromHandle(local->viewModel());
    if (!viewModel)
        return;

    const auto viewModelWeapon = interfaces->entityList->getEntityFromHandle(viewModel->weapon());
    if (!viewModelWeapon)
        return;

    const auto def = memory->itemSystem()->getItemSchema()->getItemDefinitionInterface(viewModelWeapon->itemDefinitionIndex());
    if (!def)
        return;

    viewModel->modelIndex() = interfaces->modelInfo->getModelIndex(def->getPlayerDisplayModel());

    const auto worldModel = interfaces->entityList->getEntityFromHandle(viewModelWeapon->weaponWorldModel());
    if (!worldModel)
        return;

    worldModel->modelIndex() = interfaces->modelInfo->getModelIndex(def->getWorldDisplayModel());
}

static void applyWeapons(CSPlayerInventory& localInventory, Entity* local) noexcept
{
    const auto localTeam = local->getTeamNumber();
    const auto localXuid = local->getSteamId();
    const auto itemSchema = memory->itemSystem()->getItemSchema();

    const auto highestEntityIndex = interfaces->entityList->getHighestEntityIndex();
    for (int i = memory->globalVars->maxClients + 1; i <= highestEntityIndex; ++i) {
        const auto entity = interfaces->entityList->getEntity(i);
        if (!entity || !entity->isWeapon())
            continue;

        const auto weapon = entity;
        if (weapon->originalOwnerXuid() != localXuid)
            continue;

        const auto& definitionIndex = weapon->itemDefinitionIndex();
        if (Helpers::isKnife(definitionIndex))
            continue;

        const auto def = itemSchema->getItemDefinitionInterface(definitionIndex);
        if (!def)
            continue;

        const auto loadoutSlot = def->getLoadoutSlot(localTeam);
        const auto itemView = localInventory.getItemInLoadout(localTeam, loadoutSlot);
        if (!itemView)
            continue;

        const auto soc = memory->getSOCData(itemView);
        if (!soc || soc->weaponId != definitionIndex || !Inventory::getItem(soc->itemID))
            continue;

        weapon->accountID() = localInventory.getAccountID();
        weapon->itemIDHigh() = std::uint32_t(soc->itemID >> 32);
        weapon->itemIDLow() = std::uint32_t(soc->itemID & 0xFFFFFFFF);
    }
}

static void onPostDataUpdateStart(int localHandle) noexcept
{
    const auto local = interfaces->entityList->getEntityFromHandle(localHandle);
    if (!local)
        return;

    const auto localInventory = memory->inventoryManager->getLocalInventory();
    if (!localInventory)
        return;

    applyKnife(*localInventory, local);
    applyWeapons(*localInventory, local);
}

static bool hudUpdateRequired{ false };

static void updateHud() noexcept
{
    if (auto hud_weapons = memory->findHudElement(memory->hud, "CCSGO_HudWeaponSelection") - WIN32_LINUX(0x28, 62)) {
        for (int i = 0; i < *(hud_weapons + WIN32_LINUX(32, 52)); i++)
            i = memory->clearHudWeapon(hud_weapons, i);
    }
    hudUpdateRequired = false;
}

void InventoryChanger::deleteItem(std::uint64_t itemID) noexcept
{
    if (const auto item = Inventory::getItem(itemID))
        item->markToDelete();
}

void InventoryChanger::acknowledgeItem(std::uint64_t itemID) noexcept
{
    if (Inventory::getItem(itemID) == nullptr)
        return;

    const auto localInventory = memory->inventoryManager->getLocalInventory();
    if (!localInventory)
        return;

    if (const auto view = memory->findOrCreateEconItemViewForItemID(itemID)) {
        if (const auto soc = memory->getSOCData(view)) {
            soc->inventory = localInventory->getHighestIDs().second;
            localInventory->soUpdated(localInventory->getSOID(), (SharedObject*)soc, 4);
        }
    }
}

static void applyMusicKit(CSPlayerInventory& localInventory) noexcept
{
    if (!localPlayer)
        return;

    const auto pr = *memory->playerResource;
    if (pr == nullptr)
        return;

    const auto itemView = localInventory.getItemInLoadout(Team::None, 54);
    if (!itemView)
        return;

    const auto soc = memory->getSOCData(itemView);
    if (!soc)
        return;

    const auto item = Inventory::getItem(soc->itemID);
    if (!item || !item->isMusic())
        return;

    const auto& itemData = StaticData::paintKits()[item->get().dataIndex];
    pr->musicID()[localPlayer->index()] = itemData.id;
}

static void applyPlayerAgent(CSPlayerInventory& localInventory) noexcept
{
    if (!localPlayer)
        return;

    const auto itemView = localInventory.getItemInLoadout(localPlayer->getTeamNumber(), 38);
    if (!itemView)
        return;

    const auto soc = memory->getSOCData(itemView);
    if (!soc)
        return;

    const auto item = Inventory::getItem(soc->itemID);
    if (!item || !item->isAgent())
        return;

    const auto def = memory->itemSystem()->getItemSchema()->getItemDefinitionInterface(item->get().weaponID);
    if (!def)
        return;

    const auto model = def->getPlayerDisplayModel();
    if (!model)
        return;

    const auto& dynamicData = Inventory::dynamicAgentData(item->getDynamicDataIndex());
    for (std::size_t i = 0; i < dynamicData.patches.size(); ++i) {
        if (const auto& patch = dynamicData.patches[i]; patch.patchID != 0)
            localPlayer->playerPatchIndices()[i] = patch.patchID;
    }

    const auto idx = interfaces->modelInfo->getModelIndex(model);
    localPlayer->setModelIndex(idx);

    if (const auto ragdoll = interfaces->entityList->getEntityFromHandle(localPlayer->ragdoll()))
        ragdoll->setModelIndex(idx);
}

static void applyMedal(CSPlayerInventory& localInventory) noexcept
{
    if (!localPlayer)
        return;

    const auto pr = *memory->playerResource;
    if (!pr)
        return;

    const auto itemView = localInventory.getItemInLoadout(Team::None, 55);
    if (!itemView)
        return;

    const auto soc = memory->getSOCData(itemView);
    if (!soc)
        return;

    const auto item = Inventory::getItem(soc->itemID);
    if (!item || !item->isCollectible())
        return;

    pr->activeCoinRank()[localPlayer->index()] = static_cast<int>(item->get().weaponID);
}

void InventoryChanger::run(FrameStage stage) noexcept
{
    static int localPlayerHandle = -1;

    if (localPlayer)
        localPlayerHandle = localPlayer->handle();

    if (stage == FrameStage::NET_UPDATE_POSTDATAUPDATE_START) {
        onPostDataUpdateStart(localPlayerHandle);
        if (hudUpdateRequired && localPlayer && !localPlayer->isDormant())
            updateHud();
    }

    if (stage != FrameStage::RENDER_START)
        return;

    const auto localInventory = memory->inventoryManager->getLocalInventory();
    if (!localInventory)
        return;

    if (localPlayer)
        applyGloves(*localInventory, localPlayer.get());

    applyMusicKit(*localInventory);
    applyPlayerAgent(*localInventory);
    applyMedal(*localInventory);

    ToolUser::preAddItems(*localInventory);
    Inventory::runFrame();
}

void InventoryChanger::scheduleHudUpdate() noexcept
{
    interfaces->cvar->findVar("cl_fullupdate")->changeCallback();
    hudUpdateRequired = true;
}

void InventoryChanger::overrideHudIcon(GameEvent& event) noexcept
{
    if (!localPlayer)
        return;

    if (event.getInt("attacker") != localPlayer->getUserId())
        return;

    if (const auto weapon = std::string_view{ event.getString("weapon") }; weapon != "knife" && weapon != "knife_t")
        return;

    const auto localInventory = memory->inventoryManager->getLocalInventory();
    if (!localInventory)
        return;

    const auto itemView = localInventory->getItemInLoadout(localPlayer->getTeamNumber(), 0);
    if (!itemView)
        return;

    const auto soc = memory->getSOCData(itemView);
    if (!soc || Inventory::getItem(soc->itemID) == nullptr)
        return;

    if (const auto def = memory->itemSystem()->getItemSchema()->getItemDefinitionInterface(soc->weaponId)) {
        if (const auto defName = def->getDefinitionName(); defName && std::string_view{ defName }.starts_with("weapon_"))
            event.setString("weapon", defName + 7);
    }
}

void InventoryChanger::updateStatTrak(GameEvent& event) noexcept
{
    if (!localPlayer)
        return;

    if (const auto localUserId = localPlayer->getUserId(); event.getInt("attacker") != localUserId || event.getInt("userid") == localUserId)
        return;

    const auto localInventory = memory->inventoryManager->getLocalInventory();
    if (!localInventory)
        return;

    const auto weapon = localPlayer->getActiveWeapon();
    if (!weapon)
        return;

    const auto itemID = weapon->itemID();
    const auto item = Inventory::getItem(itemID);
    if (!item || !item->isSkin())
        return;

    const auto itemView = memory->getInventoryItemByItemID(localInventory, itemID);
    if (!itemView)
        return;

    const auto soc = memory->getSOCData(itemView);
    if (!soc)
        return;

    auto& dynamicData = Inventory::dynamicSkinData(item->getDynamicDataIndex());
    if (dynamicData.statTrak > -1) {
        ++dynamicData.statTrak;
        soc->setStatTrak(dynamicData.statTrak);
        localInventory->soUpdated(localInventory->getSOID(), (SharedObject*)soc, 4);
    }
}

void InventoryChanger::onRoundMVP(GameEvent& event) noexcept
{
    if (!localPlayer)
        return;

    if (const auto localUserId = localPlayer->getUserId(); event.getInt("userid") != localUserId)
        return;

    const auto localInventory = memory->inventoryManager->getLocalInventory();
    if (!localInventory)
        return;

    const auto itemView = localInventory->getItemInLoadout(Team::None, 54);
    if (!itemView)
        return;

    const auto soc = memory->getSOCData(itemView);
    if (!soc)
        return;

    const auto item = Inventory::getItem(soc->itemID);
    if (!item || !item->isMusic())
        return;

    auto& dynamicData = Inventory::dynamicMusicData(item->getDynamicDataIndex());
    if (dynamicData.statTrak > -1) {
        ++dynamicData.statTrak;
        event.setInt("musickitmvps", dynamicData.statTrak);
        soc->setStatTrak(dynamicData.statTrak);
        localInventory->soUpdated(localInventory->getSOID(), (SharedObject*)soc, 4);
    }
}




static ImTextureID getItemIconTexture(const std::string& iconpath) noexcept;

namespace ImGui
{
    static bool SkinSelectable(const StaticData::GameItem& item, const ImVec2& iconSizeSmall, const ImVec2& iconSizeLarge, ImU32 rarityColor, bool selected, int* toAddCount = nullptr) noexcept
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;

        const auto itemName = StaticData::getWeaponName(item.weaponID).data();
        const auto itemNameSize = CalcTextSize(itemName, nullptr);

        const auto paintKitName = item.hasPaintKit() ? StaticData::paintKits()[item.dataIndex].name.c_str() : "";
        const auto paintKitNameSize = CalcTextSize(paintKitName, nullptr);

        PushID(itemName);
        PushID(paintKitName);
        const auto id = window->GetID(0);
        PopID();
        PopID();

        const auto height = ImMax(paintKitNameSize.y, ImMax(itemNameSize.y, iconSizeSmall.y));
        const auto rarityBulletRadius = IM_FLOOR(height * 0.2f);
        const auto size = ImVec2{ iconSizeSmall.x + rarityBulletRadius * 2.0f + itemNameSize.x + paintKitNameSize.x, height };

        ImVec2 pos = window->DC.CursorPos;
        pos.y += window->DC.CurrLineTextBaseOffset;
        ItemSize(size, 0.0f);

        const auto smallIconMin = pos;
        const auto smallIconMax = smallIconMin + iconSizeSmall;

        const auto rarityBulletPos = ImVec2{ pos.x + iconSizeSmall.x + 5.0f + rarityBulletRadius, pos.y + IM_FLOOR(size.y * 0.5f) };

        const auto itemNameMin = ImVec2{ rarityBulletPos.x + rarityBulletRadius + 5.0f, pos.y };
        const auto itemNameMax = itemNameMin + ImVec2{ itemNameSize.x, size.y };

        const auto separatorHeightInv = IM_FLOOR(height * 0.2f);
        const auto separatorMin = ImVec2{ itemNameMax.x + 5.0f, pos.y + separatorHeightInv };
        const auto separatorMax = separatorMin + ImVec2{ 1.0f, height - 2.0f * separatorHeightInv };

        const auto paintKitNameMin = ImVec2{ separatorMax.x + 5.0f, pos.y };
        const auto paintKitNameMax = paintKitNameMin + ImVec2{ paintKitNameSize.x, size.y };

        // Selectables are meant to be tightly packed together with no click-gap, so we extend their box to cover spacing between selectable.
        ImRect bb(pos, pos + ImVec2{ ImMax(size.x, window->WorkRect.Max.x - pos.x), size.y });
        const float spacingX = style.ItemSpacing.x;
        const float spacingY = style.ItemSpacing.y;
        const float spacingL = IM_FLOOR(spacingX * 0.50f);
        const float spacingU = IM_FLOOR(spacingY * 0.50f);
        bb.Min.x -= spacingL;
        bb.Min.y -= spacingU;
        bb.Max.x += (spacingX - spacingL);
        bb.Max.y += (spacingY - spacingU);

        if (!ItemAdd(bb, id))
            return false;

        const ImRect selectableBB{ bb.Min, ImVec2{ bb.Max.x - (selected ? 90.0f : 0.0f), bb.Max.y} };
        // We use NoHoldingActiveID on menus so user can click and _hold_ on a menu then drag to browse child entries
        ImGuiButtonFlags buttonFlags = 0;
        bool hovered, held;
        bool pressed = ButtonBehavior(selectableBB, id, &hovered, &held, buttonFlags);

        // Update NavId when clicking or when Hovering (this doesn't happen on most widgets), so navigation can be resumed with gamepad/keyboard
        if (pressed) {
            if (!g.NavDisableMouseHover && g.NavWindow == window && g.NavLayer == window->DC.NavLayerCurrent) {
                SetNavID(id, window->DC.NavLayerCurrent, window->DC.NavFocusScopeIdCurrent, ImRect(bb.Min - window->Pos, bb.Max - window->Pos));
                g.NavDisableHighlight = true;
            }
            MarkItemEdited(id);
        }

        if (hovered || selected) {
            const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_HeaderActive : hovered ? ImGuiCol_HeaderHovered : ImGuiCol_Header);
            RenderFrame(bb.Min, bb.Max, col, false, 0.0f);
            RenderNavHighlight(bb, id, ImGuiNavHighlightFlags_TypeThin | ImGuiNavHighlightFlags_NoRounding);
        }

        if (const auto icon = getItemIconTexture(item.iconPath)) {
            window->DrawList->AddImage(icon, smallIconMin, smallIconMax);
            if (g.HoveredWindow == window && IsMouseHoveringRect(bb.Min, ImVec2{ bb.Min.x + iconSizeSmall.x, bb.Max.y })) {
                BeginTooltip();
                Image(icon, iconSizeLarge);
                EndTooltip();
            }
        }

        window->DrawList->AddCircleFilled(rarityBulletPos, rarityBulletRadius + 1.0f, IM_COL32(0, 0, 0, (std::min)(120u, (rarityColor & IM_COL32_A_MASK))), 12);
        window->DrawList->AddCircleFilled(rarityBulletPos, rarityBulletRadius, rarityColor, 12);

        RenderTextClipped(itemNameMin, itemNameMax, itemName, nullptr, &itemNameSize, { 0.0f, 0.5f }, &bb);
        if (paintKitName[0] != '\0')
            window->DrawList->AddRectFilled(separatorMin, separatorMax, GetColorU32(ImGuiCol_Text));
        RenderTextClipped(paintKitNameMin, paintKitNameMax, paintKitName, nullptr, &paintKitNameSize, { 0.0f, 0.5f }, &bb);

        if (selected && toAddCount) {
            const auto cursorPosNext = window->DC.CursorPos.y;
            SameLine(window->WorkRect.Max.x - pos.x - 90.0f);
            const auto cursorPosBackup = window->DC.CursorPos.y;

            window->DC.CursorPos.y += (size.y - GetFrameHeight()) * 0.5f;
            SetNextItemWidth(80.0f);
            InputInt("", toAddCount);
            *toAddCount = (std::max)(*toAddCount, 1);

            window->DC.CursorPosPrevLine.y = cursorPosBackup;
            window->DC.CursorPos.y = cursorPosNext;
        }

        if (pressed && (window->Flags & ImGuiWindowFlags_Popup) && !(window->DC.ItemFlags & ImGuiItemFlags_SelectableDontClosePopup))
            CloseCurrentPopup();

        return pressed;
    }

    static void SkinItem(const StaticData::GameItem& item, const ImVec2& iconSizeSmall, const ImVec2& iconSizeLarge, ImU32 rarityColor, bool& shouldDelete) noexcept
    {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return;

        const ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;

        const auto itemName = StaticData::getWeaponName(item.weaponID).data();
        const auto itemNameSize = CalcTextSize(itemName, nullptr);

        const auto paintKitName = item.hasPaintKit() ? StaticData::paintKits()[item.dataIndex].name.c_str() : "";
        const auto paintKitNameSize = CalcTextSize(paintKitName, nullptr);

        PushID(itemName);
        PushID(paintKitName);
        const auto id = window->GetID(0);
        PopID();
        PopID();

        const auto height = ImMax(paintKitNameSize.y, ImMax(itemNameSize.y, iconSizeSmall.y));
        const auto rarityBulletRadius = IM_FLOOR(height * 0.2f);
        const auto size = ImVec2{ iconSizeSmall.x + rarityBulletRadius * 2.0f + itemNameSize.x + paintKitNameSize.x, height };

        ImVec2 pos = window->DC.CursorPos;
        pos.y += window->DC.CurrLineTextBaseOffset;
        ItemSize(size, 0.0f);

        const auto smallIconMin = pos;
        const auto smallIconMax = smallIconMin + iconSizeSmall;

        const auto rarityBulletPos = ImVec2{ pos.x + iconSizeSmall.x + 5.0f + rarityBulletRadius, pos.y + IM_FLOOR(size.y * 0.5f) };

        const auto itemNameMin = ImVec2{ rarityBulletPos.x + rarityBulletRadius + 5.0f, pos.y };
        const auto itemNameMax = itemNameMin + ImVec2{ itemNameSize.x, size.y };

        const auto separatorHeightInv = IM_FLOOR(height * 0.2f);
        const auto separatorMin = ImVec2{ itemNameMax.x + 5.0f, pos.y + separatorHeightInv };
        const auto separatorMax = separatorMin + ImVec2{ 1.0f, height - 2.0f * separatorHeightInv };

        const auto paintKitNameMin = ImVec2{ separatorMax.x + 5.0f, pos.y };
        const auto paintKitNameMax = paintKitNameMin + ImVec2{ paintKitNameSize.x, size.y };

        // Selectables are meant to be tightly packed together with no click-gap, so we extend their box to cover spacing between selectable.
        ImRect bb(pos, pos + ImVec2{ ImMax(size.x, window->WorkRect.Max.x - pos.x), size.y });
        const float spacingX = style.ItemSpacing.x;
        const float spacingY = style.ItemSpacing.y;
        const float spacingL = IM_FLOOR(spacingX * 0.50f);
        const float spacingU = IM_FLOOR(spacingY * 0.50f);
        bb.Min.x -= spacingL;
        bb.Min.y -= spacingU;
        bb.Max.x += (spacingX - spacingL);
        bb.Max.y += (spacingY - spacingU);

        if (!ItemAdd(bb, id))
            return;

        if (const bool hovered = (g.HoveredWindow == window && IsMouseHoveringRect(bb.Min, bb.Max))) {
            const ImU32 col = GetColorU32(ImGuiCol_HeaderHovered);
            RenderFrame(bb.Min, bb.Max, col, false, 0.0f);
            RenderNavHighlight(bb, id, ImGuiNavHighlightFlags_TypeThin | ImGuiNavHighlightFlags_NoRounding);
        }

        if (const auto icon = getItemIconTexture(item.iconPath)) {
            window->DrawList->AddImage(icon, smallIconMin, smallIconMax);
            if (g.HoveredWindow == window && IsMouseHoveringRect(bb.Min, ImVec2{ bb.Min.x + iconSizeSmall.x, bb.Max.y })) {
                BeginTooltip();
                Image(icon, iconSizeLarge);
                EndTooltip();
            }
        }

        window->DrawList->AddCircleFilled(rarityBulletPos, rarityBulletRadius + 1.0f, IM_COL32(0, 0, 0, (std::min)(120u, (rarityColor & IM_COL32_A_MASK))), 12);
        window->DrawList->AddCircleFilled(rarityBulletPos, rarityBulletRadius, rarityColor, 12);

        RenderTextClipped(itemNameMin, itemNameMax, itemName, nullptr, &itemNameSize, { 0.0f, 0.5f }, &bb);
        if (paintKitName[0] != '\0')
            window->DrawList->AddRectFilled(separatorMin, separatorMax, GetColorU32(ImGuiCol_Text));
        RenderTextClipped(paintKitNameMin, paintKitNameMax, paintKitName, nullptr, &paintKitNameSize, { 0.0f, 0.5f }, &bb);

        const auto removeButtonSize = CalcTextSize("Delete", nullptr) + style.FramePadding * 2.0f;
        const auto cursorPosNext = window->DC.CursorPos.y;
        SameLine(window->WorkRect.Max.x - pos.x - removeButtonSize.x - 7.0f);
        const auto cursorPosBackup = window->DC.CursorPos.y;

        window->DC.CursorPos.y += (size.y - GetFrameHeight()) * 0.5f;
        if (Button("Delete"))
            shouldDelete = true;

        window->DC.CursorPosPrevLine.y = cursorPosBackup;
        window->DC.CursorPos.y = cursorPosNext;
    }
}


void InventoryChanger::clearInventory() noexcept
{
    resetConfig();
}

static std::size_t lastEquippedCount = 0;
void InventoryChanger::onItemEquip(Team team, int slot, std::uint64_t itemID) noexcept
{
    const auto localInventory = memory->inventoryManager->getLocalInventory();
    if (!localInventory)
        return;

    const auto item = Inventory::getItem(itemID);
    if (!item)
        return;

    if (item->isCollectible() || item->isServiceMedal()) {
        if (const auto view = memory->getInventoryItemByItemID(localInventory, itemID)) {
            if (const auto econItem = memory->getSOCData(view))
                localInventory->soUpdated(localInventory->getSOID(), (SharedObject*)econItem, 4);
        }
    }
    else if (item->isSkin()) {
        const auto view = localInventory->getItemInLoadout(team, slot);
        memory->inventoryManager->equipItemInSlot(team, slot, (std::uint64_t(0xF) << 60) | static_cast<short>(item->get().weaponID));
        if (view) {
            if (const auto econItem = memory->getSOCData(view))
                localInventory->soUpdated(localInventory->getSOID(), (SharedObject*)econItem, 4);
        }
        ++lastEquippedCount;
    }
}

void InventoryChanger::onSoUpdated(SharedObject* object) noexcept
{
    if (lastEquippedCount > 0 && object->getTypeID() == 43 /* = k_EEconTypeDefaultEquippedDefinitionInstanceClient */) {
        *reinterpret_cast<WeaponId*>(std::uintptr_t(object) + WIN32_LINUX(0x10, 0x1C)) = WeaponId::None;
        --lastEquippedCount;
    }
}

[[nodiscard]] static bool isDefaultKnifeNameLocalizationString(std::string_view string) noexcept
{
    return string == "#SFUI_WPNHUD_Knife" || string == "#SFUI_WPNHUD_Knife_T";
}

static void appendProtobufString(std::string_view string, std::vector<char>& buffer) noexcept
{
    assert(string.length() < 128);
    buffer.push_back(0x1A);
    buffer.push_back(static_cast<char>(string.length()));
    std::ranges::copy(string, std::back_inserter(buffer));
}

[[nodiscard]] static std::vector<char> buildTextUserMessage(int destination, std::string_view string1, std::string_view string2, std::string_view string3 = {}) noexcept
{
    std::vector<char> buffer{ 0x8, static_cast<char>(destination) };
    appendProtobufString(string1, buffer);
    appendProtobufString(string2, buffer);
    appendProtobufString(string3, buffer);
    // game client expects text protobuf to contain 5 strings
    appendProtobufString("", buffer);
    appendProtobufString("", buffer);
    return buffer;
}

void InventoryChanger::onUserTextMsg(const void*& data, int& size) noexcept
{
    if (!localPlayer)
        return;

    const auto localInventory = memory->inventoryManager->getLocalInventory();
    if (!localInventory)
        return;

    const auto itemView = localInventory->getItemInLoadout(localPlayer->getTeamNumber(), 0);
    if (!itemView)
        return;

    const auto soc = memory->getSOCData(itemView);
    if (!soc)
        return;

    if (const auto item = Inventory::getItem(soc->itemID); !item || !item->isSkin())
        return;

    constexpr auto HUD_PRINTTALK = 3;
    constexpr auto HUD_PRINTCENTER = 4;
    // https://github.com/SteamDatabase/Protobufs/blob/017f1710737b7026cdd6d7e602f96a66dddb7b2e/csgo/cstrike15_usermessages.proto#L128-L131

    const auto reader = ProtobufReader{ static_cast<const std::uint8_t*>(data), size };

    if (reader.readInt32(1) == HUD_PRINTCENTER) {
        const auto strings = reader.readRepeatedString(3);
        if (strings.size() < 2)
            return;

        if (strings[0] != "#SFUI_Notice_CannotDropWeapon" &&
            strings[0] != "#SFUI_Notice_YouDroppedWeapon")
            return;

        if (!isDefaultKnifeNameLocalizationString(strings[1]))
            return;

        const auto itemSchema = memory->itemSystem()->getItemSchema();
        if (!itemSchema)
            return;

        const auto def = itemSchema->getItemDefinitionInterface(soc->weaponId);
        if (!def)
            return;

        static std::vector<char> buffer;
        buffer = buildTextUserMessage(HUD_PRINTCENTER, strings[0], def->getItemBaseName());
        data = buffer.data();
        size = static_cast<int>(buffer.size());
    }
    else if (reader.readInt32(1) == HUD_PRINTTALK) {
        const auto strings = reader.readRepeatedString(3);
        if (strings.size() < 3)
            return;

        if (strings[0] != "#Player_Cash_Award_Killed_Enemy" &&
            strings[0] != "#Player_Point_Award_Killed_Enemy" &&
            strings[0] != "#Player_Point_Award_Killed_Enemy_Plural")
            return;

        if (!isDefaultKnifeNameLocalizationString(strings[2]))
            return;

        const auto itemSchema = memory->itemSystem()->getItemSchema();
        if (!itemSchema)
            return;

        const auto def = itemSchema->getItemDefinitionInterface(soc->weaponId);
        if (!def)
            return;

        static std::vector<char> buffer;
        buffer = buildTextUserMessage(HUD_PRINTTALK, strings[0], strings[1], def->getItemBaseName());
        data = buffer.data();
        size = static_cast<int>(buffer.size());
    }
}

static std::uint64_t stringToUint64(const char* str) noexcept
{
    std::uint64_t result = 0;
    std::from_chars(str, str + std::strlen(str), result);
    return result;
}

void InventoryChanger::getArgAsStringHook(const char* string, std::uintptr_t returnAddress) noexcept
{
    if (returnAddress == memory->useToolGetArgAsStringReturnAddress) {
        ToolUser::setTool(stringToUint64(string));
    }
    else if (returnAddress == memory->useToolGetArg2AsStringReturnAddress) {
        ToolUser::setItemToApplyTool(stringToUint64(string));
    }
    else if (returnAddress == memory->wearItemStickerGetArgAsStringReturnAddress) {
        ToolUser::setItemToWearSticker(stringToUint64(string));
    }
    else if (returnAddress == memory->setNameToolStringGetArgAsStringReturnAddress) {
        ToolUser::setNameTag(string);
    }
    else if (returnAddress == memory->clearCustomNameGetArgAsStringReturnAddress) {
        ToolUser::setItemToRemoveNameTag(stringToUint64(string));
    }
    else if (returnAddress == memory->deleteItemGetArgAsStringReturnAddress) {
        InventoryChanger::deleteItem(stringToUint64(string));
    }
    else if (returnAddress == memory->acknowledgeNewItemByItemIDGetArgAsStringReturnAddress) {
        InventoryChanger::acknowledgeItem(stringToUint64(string));
    }
    else if (returnAddress == memory->setStatTrakSwapToolItemsGetArgAsStringReturnAddress1) {
        ToolUser::setStatTrakSwapItem1(stringToUint64(string));
    }
    else if (returnAddress == memory->setStatTrakSwapToolItemsGetArgAsStringReturnAddress2) {
        ToolUser::setStatTrakSwapItem2(stringToUint64(string));
    }
}

void InventoryChanger::getArgAsNumberHook(int number, std::uintptr_t returnAddress) noexcept
{
    if (returnAddress == memory->setStickerToolSlotGetArgAsNumberReturnAddress || returnAddress == memory->wearItemStickerGetArgAsNumberReturnAddress)
        ToolUser::setStickerSlot(number);
}

struct Icon {
    Texture texture;
    int lastReferencedFrame = 0;
};

static std::unordered_map<std::string, Icon> iconTextures;

static ImTextureID getItemIconTexture(const std::string& iconpath) noexcept
{
    if (iconpath.empty())
        return 0;

    auto& icon = iconTextures[iconpath];
    if (!icon.texture.get()) {
        static int frameCount = 0;
        static float timeSpentThisFrame = 0.0f;
        static int loadedThisFrame = 0;

        if (frameCount != ImGui::GetFrameCount()) {
            frameCount = ImGui::GetFrameCount();
            timeSpentThisFrame = 0.0f;
            // memory->debugMsg("LOADED %d ICONS\n", loadedThisFrame);
            loadedThisFrame = 0;
        }

        if (timeSpentThisFrame > 0.01f)
            return 0;

        ++loadedThisFrame;

        const auto start = std::chrono::high_resolution_clock::now();

        auto handle = interfaces->baseFileSystem->open(("resource/flash/" + iconpath + (iconpath.find("status_icons") != std::string::npos ? "" : "_large") + ".png").c_str(), "r", "GAME");
        if (!handle)
            handle = interfaces->baseFileSystem->open(("resource/flash/" + iconpath + ".png").c_str(), "r", "GAME");

        assert(handle);
        if (handle) {
            if (const auto size = interfaces->baseFileSystem->size(handle); size > 0) {
                const auto buffer = std::make_unique<std::uint8_t[]>(size);
                if (interfaces->baseFileSystem->read(buffer.get(), size, handle) > 0) {
                    int width, height;
                    stbi_set_flip_vertically_on_load_thread(false);

                    if (const auto data = stbi_load_from_memory((const stbi_uc*)buffer.get(), size, &width, &height, nullptr, STBI_rgb_alpha)) {
                        icon.texture.init(width, height, data);
                        stbi_image_free(data);
                    }
                    else {
                        assert(false);
                    }
                }
            }
            interfaces->baseFileSystem->close(handle);
        }

        const auto end = std::chrono::high_resolution_clock::now();
        timeSpentThisFrame += std::chrono::duration<float>(end - start).count();
    }
    icon.lastReferencedFrame = ImGui::GetFrameCount();
    return icon.texture.get();
}

void InventoryChanger::clearItemIconTextures() noexcept
{
    iconTextures.clear();
}

void InventoryChanger::clearUnusedItemIconTextures() noexcept
{
    constexpr auto maxIcons = 30;
    const auto frameCount = ImGui::GetFrameCount();
    while (iconTextures.size() > maxIcons) {
        const auto oldestIcon = std::ranges::min_element(iconTextures, {}, [](const auto& icon) { return icon.second.lastReferencedFrame; });
        if (oldestIcon->second.lastReferencedFrame == frameCount)
            break;

        iconTextures.erase(oldestIcon);
    }
}

static int remapKnifeAnim(WeaponId weaponID, const int sequence) noexcept
{
    enum Sequence
    {
        SEQUENCE_DEFAULT_DRAW = 0,
        SEQUENCE_DEFAULT_IDLE1 = 1,
        SEQUENCE_DEFAULT_IDLE2 = 2,
        SEQUENCE_DEFAULT_LIGHT_MISS1 = 3,
        SEQUENCE_DEFAULT_LIGHT_MISS2 = 4,
        SEQUENCE_DEFAULT_HEAVY_MISS1 = 9,
        SEQUENCE_DEFAULT_HEAVY_HIT1 = 10,
        SEQUENCE_DEFAULT_HEAVY_BACKSTAB = 11,
        SEQUENCE_DEFAULT_LOOKAT01 = 12,

        SEQUENCE_BUTTERFLY_DRAW = 0,
        SEQUENCE_BUTTERFLY_DRAW2 = 1,
        SEQUENCE_BUTTERFLY_LOOKAT01 = 13,
        SEQUENCE_BUTTERFLY_LOOKAT03 = 15,

        SEQUENCE_FALCHION_IDLE1 = 1,
        SEQUENCE_FALCHION_HEAVY_MISS1 = 8,
        SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP = 9,
        SEQUENCE_FALCHION_LOOKAT01 = 12,
        SEQUENCE_FALCHION_LOOKAT02 = 13,

        SEQUENCE_DAGGERS_IDLE1 = 1,
        SEQUENCE_DAGGERS_LIGHT_MISS1 = 2,
        SEQUENCE_DAGGERS_LIGHT_MISS5 = 6,
        SEQUENCE_DAGGERS_HEAVY_MISS2 = 11,
        SEQUENCE_DAGGERS_HEAVY_MISS1 = 12,

        SEQUENCE_BOWIE_IDLE1 = 1,
    };

    switch (weaponID) {
    case WeaponId::Butterfly:
        switch (sequence) {
        case SEQUENCE_DEFAULT_DRAW:
            return Helpers::random(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
        case SEQUENCE_DEFAULT_LOOKAT01:
            return Helpers::random(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
        default:
            return sequence + 1;
        }
    case WeaponId::Falchion:
        switch (sequence) {
        case SEQUENCE_DEFAULT_IDLE2:
            return SEQUENCE_FALCHION_IDLE1;
        case SEQUENCE_DEFAULT_HEAVY_MISS1:
            return Helpers::random(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP);
        case SEQUENCE_DEFAULT_LOOKAT01:
            return Helpers::random(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02);
        case SEQUENCE_DEFAULT_DRAW:
        case SEQUENCE_DEFAULT_IDLE1:
            return sequence;
        default:
            return sequence - 1;
        }
    case WeaponId::Daggers:
        switch (sequence) {
        case SEQUENCE_DEFAULT_IDLE2:
            return SEQUENCE_DAGGERS_IDLE1;
        case SEQUENCE_DEFAULT_LIGHT_MISS1:
        case SEQUENCE_DEFAULT_LIGHT_MISS2:
            return Helpers::random(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5);
        case SEQUENCE_DEFAULT_HEAVY_MISS1:
            return Helpers::random(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1);
        case SEQUENCE_DEFAULT_HEAVY_HIT1:
        case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
        case SEQUENCE_DEFAULT_LOOKAT01:
            return sequence + 3;
        case SEQUENCE_DEFAULT_DRAW:
        case SEQUENCE_DEFAULT_IDLE1:
            return sequence;
        default:
            return sequence + 2;
        }
    case WeaponId::Bowie:
        switch (sequence) {
        case SEQUENCE_DEFAULT_DRAW:
        case SEQUENCE_DEFAULT_IDLE1:
            return sequence;
        case SEQUENCE_DEFAULT_IDLE2:
            return SEQUENCE_BOWIE_IDLE1;
        default:
            return sequence - 1;
        }
    case WeaponId::Ursus:
    case WeaponId::SkeletonKnife:
    case WeaponId::NomadKnife:
    case WeaponId::Paracord:
    case WeaponId::SurvivalKnife:
        switch (sequence) {
        case SEQUENCE_DEFAULT_DRAW:
            return Helpers::random(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
        case SEQUENCE_DEFAULT_LOOKAT01:
            return Helpers::random(SEQUENCE_BUTTERFLY_LOOKAT01, Sequence(14));
        default:
            return sequence + 1;
        }
    case WeaponId::Stiletto:
        switch (sequence) {
        case SEQUENCE_DEFAULT_LOOKAT01:
            return Helpers::random(12, 13);
        }
    case WeaponId::Talon:
        switch (sequence) {
        case SEQUENCE_DEFAULT_LOOKAT01:
            return Helpers::random(14, 15);
        }
    default:
        return sequence;
    }
}

void InventoryChanger::fixKnifeAnimation(Entity* viewModelWeapon, long& sequence) noexcept
{
    if (!localPlayer)
        return;

    if (!Helpers::isKnife(viewModelWeapon->itemDefinitionIndex()))
        return;

    const auto localInventory = memory->inventoryManager->getLocalInventory();
    if (!localInventory)
        return;

    const auto itemView = localInventory->getItemInLoadout(localPlayer->getTeamNumber(), 0);
    if (!itemView)
        return;

    if (const auto soc = memory->getSOCData(itemView); !soc || Inventory::getItem(soc->itemID) == nullptr)
        return;

    sequence = remapKnifeAnim(viewModelWeapon->itemDefinitionIndex(), sequence);
}



constexpr auto windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;






static ImFont* addFontFromVFONT(const std::string& path, float size, const ImWchar* glyphRanges, bool merge) noexcept
{
    auto file = Helpers::loadBinaryFile(path);
    if (!Helpers::decodeVFONT(file))
        return nullptr;

    ImFontConfig cfg;
    cfg.FontData = file.data();
    cfg.FontDataSize = file.size();
    cfg.FontDataOwnedByAtlas = false;
    cfg.MergeMode = merge;
    cfg.GlyphRanges = glyphRanges;
    cfg.SizePixels = size;

    return ImGui::GetIO().Fonts->AddFont(&cfg);
}



//when you init GUI, ye useless if statement


//somewhere in your menu



GUI::GUI() noexcept
{


    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowMinSize = ImVec2(715.f, 410.f);
    style.WindowPadding = ImVec2(0.00f, 0.00f);
    style.FramePadding = ImVec2(2.00f, 2.00f);
    style.CellPadding = ImVec2(2.00f, 2.00f);
    style.ItemSpacing = ImVec2(4.00f, 10.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 10.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing = 2.00f;
    style.ScrollbarSize = 8.00f;
    style.GrabMinSize = 6.00f;
    style.WindowBorderSize = 0.00f;
    style.ChildBorderSize = 1.00f;
    style.PopupBorderSize = 1.00f;
    style.FrameBorderSize = 0.00f;
    style.TabBorderSize = 0.00f;
    style.WindowRounding = 0.00f;
    style.ChildRounding = 0.00f;
    style.FrameRounding = 0.00f;
    style.PopupRounding = 0.00f;
    style.ScrollbarRounding = 0.00f;
    style.GrabRounding = 0.00f;
    style.LogSliderDeadzone = 4.00f;
    style.TabRounding = 4.00f;
    style.WindowTitleAlign = ImVec2(0.17f, 0.00f);
    style.WindowMenuButtonPosition = 0;
    style.ColorButtonPosition = 1;
    style.ButtonTextAlign = ImVec2(0.50f, 0.50f);
    style.SelectableTextAlign = ImVec2(0.50f, 0.50f);
    style.DisplaySafeAreaPadding = ImVec2(3.00f, 3.00f);



    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    ImFontConfig cfg;
    cfg.SizePixels = 15.0f;




#ifdef _WIN32
    if (PWSTR pathToFonts; SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Fonts, 0, nullptr, &pathToFonts))) {
        const std::filesystem::path path{ pathToFonts };
        CoTaskMemFree(pathToFonts);

        fonts.normal15px = io.Fonts->AddFontFromFileTTF((path / "tahoma.ttf").string().c_str(), 15.0f, &cfg, Helpers::getFontGlyphRanges());
        if (!fonts.normal15px)
            io.Fonts->AddFontDefault(&cfg);

        cfg.MergeMode = true;
        static constexpr ImWchar symbol[]{
            0x2605, 0x2605, // ★
            0
        };
        io.Fonts->AddFontFromFileTTF((path / "seguisym.ttf").string().c_str(), 15.0f, &cfg, symbol);
        cfg.MergeMode = false;
    }
#else
    fonts.normal15px = addFontFromVFONT("csgo/panorama/fonts/notosans-regular.vfont", 15.0f, Helpers::getFontGlyphRanges(), false);
#endif
    if (!fonts.normal15px)
        io.Fonts->AddFontDefault(&cfg);
    addFontFromVFONT("csgo/panorama/fonts/notosanskr-regular.vfont", 15.0f, io.Fonts->GetGlyphRangesKorean(), true);
    addFontFromVFONT("csgo/panorama/fonts/notosanssc-regular.vfont", 17.0f, io.Fonts->GetGlyphRangesChineseFull(), true);
}



void GUI::render() noexcept
{
    if (!config->style.menuStyle) {

        renderGuiStyle2();
        //renderAimbotWindow();
        AntiAim::drawGUI(false);
        renderChamsWindow();
        Sound::drawGUI(false);
        renderConfigWindow();
    }
    else {
        renderMenuBar();
        renderStyleWindow();
    }
}

void GUI::updateColors() const noexcept
{
    switch (config->style.menuColors) {
    case 0: ImGui::StyleColorsDark(); break;
    case 1: ImGui::StyleColorsLight(); break;
    case 2: ImGui::StyleColorsClassic(); break;
    }
}

void GUI::handleToggle() noexcept
{
    if (Misc::isMenuKeyPressed()) {
        open = !open;
        if (!open)
            interfaces->inputSystem->resetInputState();
#ifndef _WIN32
        ImGui::GetIO().MouseDrawCursor = gui->open;
#endif
    }
}

static void menuBarItem(const char* name, bool& enabled) noexcept
{
    if (ImGui::MenuItem(name)) {
        enabled = true;
        ImGui::SetWindowFocus(name);
        ImGui::SetWindowPos(name, { 100.0f, 100.0f });
    }
}

void GUI::renderMenuBar() noexcept
{
    if (ImGui::BeginMainMenuBar()) {
        menuBarItem("Aimbot", window.aimbot);
        AntiAim::menuBarItem();
        menuBarItem("Triggerbot", window.triggerbot);
        menuBarItem("Chams", window.chams);

        Sound::menuBarItem();
        menuBarItem("Style", window.style);

        menuBarItem("Config", window.config);
        ImGui::EndMainMenuBar();
    }
}






void GUI::renderChamsWindow(bool contentOnly) noexcept
{
    if (!contentOnly) {
        if (!window.chams)
            return;
        ImGui::SetNextWindowSize({ 0.0f, 0.0f });
        ImGui::Begin("Chams", &window.chams, windowFlags);
    }



    if (!contentOnly) {
        ImGui::End();
    }
}

void GUI::renderStyleWindow(bool contentOnly) noexcept
{
    if (!contentOnly) {
        if (!window.style)
            return;
        ImGui::SetNextWindowSize({ 0.0f, 0.0f });
        ImGui::Begin("Style", &window.style, windowFlags);
    }

    ImGui::PushItemWidth(150.0f);
    if (ImGui::Combo("Menu style", &config->style.menuStyle, "Classic\0One window\0"))
        window = { };
    if (ImGui::Combo("Menu colors", &config->style.menuColors, "Dark\0Light\0Classic\0Custom\0"))
        updateColors();
    ImGui::PopItemWidth();

    if (config->style.menuColors == 3) {
        ImGuiStyle& style = ImGui::GetStyle();
        for (int i = 0; i < ImGuiCol_COUNT; i++) {
            if (i && i & 3) ImGui::SameLine(220.0f * (i & 3));

            ImGuiCustom::colorPicker(ImGui::GetStyleColorName(i), (float*)&style.Colors[i], &style.Colors[i].w);
        }
    }

    if (!contentOnly)
        ImGui::End();
}

void GUI::renderConfigWindow(bool contentOnly) noexcept
{
    if (!contentOnly) {
        if (!window.config)
            return;
        ImGui::SetNextWindowSize({ 320.0f, 0.0f });
        if (!ImGui::Begin("Config", &window.config, windowFlags)) {
            ImGui::End();
            return;
        }
    }


    if (!contentOnly)
        ImGui::End();
}


void GUI::renderGuiStyle2() noexcept
{

    static int tabs = 1;
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.09f, 0.09f, 0.09f, 1.00f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 10.0f);
    ImGui::Begin("benzoboyz.net | ily. | s/o bal, blekleratt", nullptr, windowFlags | ImGuiWindowFlags_NoTitleBar);

    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.00f, 0.55f, 0.98f, 1.00f));
    if (GetAsyncKeyState(VK_END)) {
        hooks->uninstall();
    }

    ImGui::SetCursorPos({ 0.f,145.f });
    if (ImGui::Button("legitbot", { 156.f,30.f }))
    {
        tabs = 1;
    }
    ImGui::SetCursorPos({ 0.f,176.f });
    if (ImGui::Button("ragebot", { 156.f,30.f }))
    {
        tabs = 2;
    }
    ImGui::SetCursorPos({ 0.f,224.f });
    if (ImGui::Button("misc", { 156.f,30.f }))
    {
        tabs = 3;
    }
    ImGui::SetCursorPos({ 0.f,255.f });
    if (ImGui::Button("visuals", { 156.f,30.f }))
    {
        tabs = 4;
    }
    ImGui::SetCursorPos({ 0.f,286.f });
    if (ImGui::Button("skins", { 156.f,30.f }))
    {
        tabs = 5;
    }
    ImGui::SetCursorPos({ 0.f,331.f });
    if (ImGui::Button("settings", { 156.f,30.f }))
    {
        tabs = 7;
    }
    ImGui::SetCursorPos({ 0.f,362.f });
    if (ImGui::Button("read<3", { 156.f,30.f })) {
        tabs = 6;
    }
    ImGui::SetCursorPos({ 6.f,131.f });
    ImGui::PushItemWidth(84.000000);
    ImGui::Text("aim settings");
    ImGui::PopItemWidth();
    ImGui::SetCursorPos({ 6.f,209.f });
    ImGui::PushItemWidth(91.000000);
    ImGui::Text("visualization");
    ImGui::PopItemWidth();
    ImGui::SetCursorPos({ 6.f,316.f });
    ImGui::PushItemWidth(56.000000);
    ImGui::Text("settings");
    ImGui::PopItemWidth();


    //legit bot redisgn asap
    if (tabs == 1) {

        ImGui::SetCursorPos({ 155.f,26.f });
        ImGui::BeginChild("child0", { 541.f,366.f }, true);

        ImGui::SetCursorPos({ 22.f,2.f });
        ImGui::PushItemWidth(140.000000);
        ImGui::Text("weapon configuration");
        ImGui::PopItemWidth();

        ImGui::SetCursorPos({ 281.f,71.f });
        ImGui::PushItemWidth(70.000000);
        ImGui::Text("triggerbot");
        ImGui::PopItemWidth();

        ImGui::SetCursorPos({ 281.f,215.f });
        ImGui::PushItemWidth(63.000000);
        ImGui::Text("backtrack");
        ImGui::PopItemWidth();

        ImGui::SetCursorPos({ 23.f,71.f });
        ImGui::PushItemWidth(42.000000);
        ImGui::Text("aimbot");
        ImGui::PopItemWidth();
        ImGui::EndChild();

        ImGui::SetCursorPos({ 173.f,44.f });
        ImGui::BeginChild("child1", { 508.f,50.f }, true);
        static int legitbot = 0;
        ImGui::SetCursorPos({ 261.f,7.f });
        if (ImGui::Button("smg", { 95.f,40.f }))
        {
            legitbot = 3;
        }
        ImGui::SetCursorPos({ 384.f,7.f });
        if (ImGui::Button("heavy", { 90.f,40.f }))
        {
            legitbot = 5;
        }
        ImGui::SetCursorPos({ 144.f,7.f });
        if (ImGui::Button("rifle", { 95.f,40.f }))
        {
            legitbot = 4;
        }
        ImGui::SetCursorPos({ 21.f,7.f });
        if (ImGui::Button("pistols", { 95.f,40.f }))
        {
            legitbot = 2;
        }
        static int currentCategory{ 0 };
        static int currentWeapon{ 0 };
        if (legitbot == 1) {
            switch (currentCategory) {

                currentWeapon = 0;
            }
        }
        if (legitbot == 2) {

            static int currentPistol{ 0 };
            static constexpr const char* pistols[]{ "-" };
            currentWeapon = currentPistol ? currentPistol : 35;
        }
        if (legitbot == 5) {
            static int currentHeavy{ 0 };
            static constexpr const char* heavies[]{ "-" };
            currentWeapon = currentHeavy ? currentHeavy + 10 : 36;
        }
        if (legitbot == 3) {

            static int currentSmg{ 0 };
            static constexpr const char* smgs[]{ " " };
            currentWeapon = currentSmg ? currentSmg + 16 : 37;
        }
        if (legitbot == 4) {

            static int currentRifle{ 0 };
            static constexpr const char* rifles[]{ " " };
            currentWeapon = currentRifle ? currentRifle + 23 : 38;
        }
        ImGui::EndChild();



        ImGui::SetCursorPos({ 172.f,111.f });
        ImGui::BeginChild("child2", { 250.f,268.f }, true);

        ImGui::SetCursorPos({ 10.f,110.f });
        ImGui::Checkbox("Visible only", &config->aimbot[currentWeapon].visibleOnly);
        ImGui::SetCursorPos({ 10.f,10.f });
        ImGui::Checkbox("Enabled", &config->aimbot[currentWeapon].enabled);
        ImGui::SetCursorPos({ 10.f,35.f });
        ImGui::Checkbox("activation on key", &config->aimbotOnKey);
        ImGui::SetCursorPos({ 10.f,160.f });
        ImGui::Checkbox("Ignore smoke", &config->aimbot[currentWeapon].ignoreSmoke);

        ImGui::SetCursorPos({ 10.f,85.f });
        ImGui::Checkbox("Silent", &config->aimbot[currentWeapon].silent);
        ImGui::SetCursorPos({ 10.f,60.f });
        ImGui::Checkbox("Aimlock", &config->aimbot[currentWeapon].aimlock);
        ImGui::SetCursorPos({ 10.f,135.f });
        ImGui::Checkbox("Ignore flash", &config->aimbot[currentWeapon].ignoreFlash);
        ImGui::SetCursorPos({ 10.f,185.f });
        ImGui::Checkbox("Friendly fire", &config->aimbot[currentWeapon].friendlyFire);

        ImGui::SetCursorPos({ 105.f,10.f });
        ImGui::PushItemWidth(70.000000);
        ImGui::PushID("Aimbot Key");
        ImGui::hotkey("", config->aimbotKey);
        ImGui::PopItemWidth();

        ImGui::SetCursorPos({ 10.f,310.f });
        ImGui::PushItemWidth(215.000000);
        ImGui::SliderFloat("smoothing", &config->aimbot[currentWeapon].smooth, 1.0f, 100.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::SetCursorPos({ 10.f,350.f });
        ImGui::PushItemWidth(215.000000);
        ImGui::SliderFloat("1st shot accuracy (max prefered)", &config->aimbot[currentWeapon].maxShotInaccuracy, 0.0f, 1.0f, "%.5f", ImGuiSliderFlags_Logarithmic);
        ImGui::PopItemWidth();

        ImGui::SetCursorPos({ 10.f,390.f });
        ImGui::PushItemWidth(215.000000);
        ImGui::SliderFloat("aim accuracy (max prefered)", &config->aimbot[currentWeapon].maxAimInaccuracy, 0.0f, 1.0f, "%.5f", ImGuiSliderFlags_Logarithmic);
        ImGui::PopItemWidth();

        ImGui::SetCursorPos({ 10.f,270.f });
        ImGui::PushItemWidth(215.000000);
        ImGui::SliderFloat("fov", &config->aimbot[currentWeapon].fov, 0.0f, 255.0f, "%.2f", ImGuiSliderFlags_Logarithmic);
        ImGui::PopItemWidth();

        ImGui::SetCursorPos({ 10.f,210.f });
        ImGui::PushItemWidth(98.000000);
        ImGui::Text("target bone");
        ImGui::PopItemWidth();

        ImGui::SetCursorPos({ 10.f,235.f });
        ImGui::PushItemWidth(105.000000);
        ImGui::Combo("Bone", &config->aimbot[currentWeapon].bone, "Nearest\0Best damage\0Head\0Neck\0Sternum\0Chest\0Stomach\0Pelvis\0");
        ImGui::PopItemWidth();
        ImGui::EndChild();




        //triggerbot
        ImGui::SetCursorPos({ 430.f,111.f });

        ImGui::BeginChild("child3", { 250.f,125.f }, true);
        static int trigCategory{ 0 };
        static int trigWeapon{ 0 };
        ImGui::PushID(1);
        switch (trigCategory) {
        case 0:
            trigWeapon = 0;

            break;
        }
        ImGui::SetCursorPos({ 105.f,10.f });
        ImGui::PushItemWidth(70.000000);
        ImGui::hotkey("", config->triggerbotHoldKey);
        ImGui::SetCursorPos({ 10.f,10.f });
        ImGui::Checkbox("enable", &config->triggerbot[trigWeapon].enabled);


        ImGui::SetCursorPos({ 10.f,35.f });
        ImGui::Checkbox("friendly fire", &config->triggerbot[trigWeapon].friendlyFire);

        ImGui::SetCursorPos({ 10.f,60.f });
        ImGui::Checkbox("ignore flash", &config->triggerbot[trigWeapon].ignoreFlash);

        ImGui::SetCursorPos({ 10.f,85.f });
        ImGui::Checkbox("ignore smoke", &config->triggerbot[trigWeapon].ignoreSmoke);

        ImGui::SetCursorPos({ 1.f,135.f });
        ImGui::PushItemWidth(205.000000);
        ImGui::SliderInt("delay (ms)", &config->triggerbot[trigWeapon].shotDelay, 0, 250, "%d ms");
        ImGui::PopItemWidth();

        ImGui::SetCursorPos({ 10.f,160.f });
        ImGui::PushItemWidth(220.000000);
        ImGui::SliderFloat("var reg (ms)", &config->triggerbot[trigWeapon].burstTime, 0.0f, 0.5f, "%.3f s");
        ImGui::PopItemWidth();



        ImGui::SetCursorPos({ 10.f,110.f });
        ImGui::Checkbox("check for kill", &config->triggerbot[trigWeapon].killshot);

        ImGui::EndChild();




        ImGui::SetCursorPos({ 430.f,254.f });
        ImGui::BeginChild("child4", { 250.f,125.f }, true);


        ImGui::SetCursorPos({ 10.f,10.f });
        ImGui::Checkbox("Enabled", &backtrackConfig.enabled);
        ImGui::SetCursorPos({ 10.f,50.f });
        ImGui::Checkbox("Ignore smoke", &backtrackConfig.ignoreSmoke);
        ImGui::SetCursorPos({ 10.f,75.f });
        ImGui::Checkbox("spray offset (30,30)", &backtrackConfig.recoilBasedFov);
        ImGui::SetCursorPos({ 10.f,100.f });
        ImGui::PushItemWidth(192.000000);
        ImGui::SliderInt("ticks", &backtrackConfig.timeLimit, 1, 200, "%d ms");
        ImGui::PopItemWidth();


        ImGui::End();

    }
    //ragebot add soon
    if (tabs == 2) {

    }
    //misc
    if (tabs == 3) {
        ImGui::SetCursorPos({ 155.f,26.f });
        ImGui::BeginChild("child0", { 541.f,366.f }, true);
        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnOffset(1, 230.0f);
        ImGui::Checkbox("Anti AFK kick", &miscConfig.antiAfkKick);
        ImGui::Checkbox("Auto strafe", &miscConfig.autoStrafe);
        ImGui::Checkbox("Bunny hop", &miscConfig.bunnyHop);
        ImGui::Checkbox("Fast duck", &miscConfig.fastDuck);
        ImGui::Checkbox("Moonwalk", &miscConfig.moonwalk);
        ImGui::Checkbox("Edge Jump", &miscConfig.edgejump);
        ImGui::SameLine();
        ImGui::PushID("Edge Jump Key");
        ImGui::hotkey("", miscConfig.edgejumpkey);
        ImGui::PopID();
        ImGui::Checkbox("Slowwalk", &miscConfig.slowwalk);
        ImGui::SameLine();
        ImGui::PushID("Slowwalk Key");
        ImGui::hotkey("", miscConfig.slowwalkKey);
        ImGui::PopID();
        ImGuiCustom::colorPicker("Noscope crosshair", miscConfig.noscopeCrosshair);
        ImGuiCustom::colorPicker("Recoil crosshair", miscConfig.recoilCrosshair);
        ImGui::Checkbox("Auto pistol", &miscConfig.autoPistol);
        ImGui::Checkbox("Auto reload", &miscConfig.autoReload);
        ImGui::Checkbox("Auto accept", &miscConfig.autoAccept);
        ImGui::Checkbox("Radar hack", &miscConfig.radarHack);
        ImGui::Checkbox("Reveal ranks", &miscConfig.revealRanks);
        ImGui::Checkbox("Reveal money", &miscConfig.revealMoney);
        ImGui::Checkbox("Reveal suspect", &miscConfig.revealSuspect);
        ImGui::Checkbox("Reveal votes", &miscConfig.revealVotes);

        ImGui::Checkbox("Spectator list", &miscConfig.spectatorList.enabled);
        ImGui::SameLine();

        ImGui::PushID("Spectator list");
        if (ImGui::Button("..."))
            ImGui::OpenPopup("");

        if (ImGui::BeginPopup("")) {
            ImGui::Checkbox("No Title Bar", &miscConfig.spectatorList.noTitleBar);
            ImGui::EndPopup();
        }
        ImGui::PopID();

        ImGui::Checkbox("Watermark", &miscConfig.watermark.enabled);
        ImGuiCustom::colorPicker("Offscreen Enemies", miscConfig.offscreenEnemies.asColor4(), &miscConfig.offscreenEnemies.enabled);
        ImGui::SameLine();
        ImGui::PushID("Offscreen Enemies");
        if (ImGui::Button("..."))
            ImGui::OpenPopup("");

        if (ImGui::BeginPopup("")) {
            ImGui::Checkbox("Health Bar", &miscConfig.offscreenEnemies.healthBar.enabled);
            ImGui::SameLine();
            ImGui::SetNextItemWidth(95.0f);
            ImGui::Combo("Type", &miscConfig.offscreenEnemies.healthBar.type, "Gradient\0Solid\0Health-based\0");
            if (miscConfig.offscreenEnemies.healthBar.type == HealthBar::Solid) {
                ImGui::SameLine();
                ImGuiCustom::colorPicker("", miscConfig.offscreenEnemies.healthBar.asColor4());
            }
            ImGui::EndPopup();
        }
        ImGui::PopID();
        ImGui::Checkbox("Fix animation LOD", &miscConfig.fixAnimationLOD);
        ImGui::Checkbox("Fix bone matrix", &miscConfig.fixBoneMatrix);
        ImGui::Checkbox("Fix movement", &miscConfig.fixMovement);
        ImGui::Checkbox("Disable model occlusion", &miscConfig.disableModelOcclusion);
        ImGui::SliderFloat("Aspect Ratio", &miscConfig.aspectratio, 0.0f, 5.0f, "%.2f");
        ImGui::NextColumn();
        ImGui::Checkbox("Disable HUD blur", &miscConfig.disablePanoramablur);
        ImGui::Checkbox("Animated clan tag", &miscConfig.animatedClanTag);
        ImGui::Checkbox("Clock tag", &miscConfig.clocktag);
        ImGui::Checkbox("Custom clantag", &miscConfig.customClanTag);
        ImGui::SameLine();
        ImGui::PushItemWidth(120.0f);
        ImGui::PushID(0);

        if (ImGui::InputText("", miscConfig.clanTag, sizeof(miscConfig.clanTag)))
            Misc::updateClanTag(true);
        ImGui::PopID();
        ImGui::Checkbox("Kill message", &miscConfig.killMessage);
        ImGui::SameLine();
        ImGui::PushItemWidth(120.0f);
        ImGui::PushID(1);
        ImGui::InputText("", &miscConfig.killMessageString);
        ImGui::PopID();
        ImGui::Checkbox("Name stealer", &miscConfig.nameStealer);
        ImGui::PushID(3);
        ImGui::SetNextItemWidth(100.0f);
        ImGui::Combo("", &miscConfig.banColor, "White\0Red\0Purple\0Green\0Light green\0Turquoise\0Light red\0Gray\0Yellow\0Gray 2\0Light blue\0Gray/Purple\0Blue\0Pink\0Dark orange\0Orange\0");
        ImGui::PopID();
        ImGui::SameLine();
        ImGui::PushID(4);
        ImGui::InputText("", &miscConfig.banText);
        ImGui::PopID();
        ImGui::SameLine();
        if (ImGui::Button("Setup fake ban"))
            Misc::fakeBan(true);
        ImGui::Checkbox("Fast plant", &miscConfig.fastPlant);
        ImGui::Checkbox("Fast Stop", &miscConfig.fastStop);
        ImGuiCustom::colorPicker("Bomb timer", miscConfig.bombTimer);
        ImGui::Checkbox("Quick reload", &miscConfig.quickReload);
        ImGui::Checkbox("Prepare revolver", &miscConfig.prepareRevolver);
        ImGui::SameLine();
        ImGui::PushID("Prepare revolver Key");
        ImGui::hotkey("", miscConfig.prepareRevolverKey);
        ImGui::PopID();
        ImGui::Combo("Hit Sound", &miscConfig.hitSound, "None\0Metal\0Gamesense\0Bell\0Glass\0Custom\0");
        if (miscConfig.hitSound == 5) {
            ImGui::InputText("Hit Sound filename", &miscConfig.customHitSound);
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("audio file must be put in csgo/sound/ directory");
        }
        ImGui::PushID(5);
        ImGui::Combo("Kill Sound", &miscConfig.killSound, "None\0Metal\0Gamesense\0Bell\0Glass\0Custom\0");
        if (miscConfig.killSound == 5) {
            ImGui::InputText("Kill Sound filename", &miscConfig.customKillSound);
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("audio file must be put in csgo/sound/ directory");
        }
        ImGui::PopID();
        ImGui::SetNextItemWidth(90.0f);
        ImGui::InputInt("Choked packets", &miscConfig.chokedPackets, 1, 5);
        miscConfig.chokedPackets = std::clamp(miscConfig.chokedPackets, 0, 64);
        ImGui::SameLine();
        ImGui::PushID("Choked packets Key");
        ImGui::hotkey("", miscConfig.chokedPacketsKey);
        ImGui::PopID();
        /*
        ImGui::Text("Quick healthshot");
        ImGui::SameLine();
        hotkey(miscConfig.quickHealthshotKey);
        */
        ImGui::Checkbox("Grenade Prediction", &miscConfig.nadePredict);
        ImGui::Checkbox("Fix tablet signal", &miscConfig.fixTabletSignal);
        ImGui::SetNextItemWidth(120.0f);
        ImGui::SliderFloat("Max angle delta", &miscConfig.maxAngleDelta, 0.0f, 255.0f, "%.2f");
        ImGui::Checkbox("Opposite Hand Knife", &miscConfig.oppositeHandKnife);
        ImGui::Checkbox("Preserve Killfeed", &miscConfig.preserveKillfeed.enabled);
        ImGui::SameLine();

        ImGui::PushID("Preserve Killfeed");
        if (ImGui::Button("..."))
            ImGui::OpenPopup("");

        if (ImGui::BeginPopup("")) {
            ImGui::Checkbox("Only Headshots", &miscConfig.preserveKillfeed.onlyHeadshots);
            ImGui::EndPopup();
        }
        ImGui::PopID();

        ImGui::Checkbox("Purchase List", &miscConfig.purchaseList.enabled);
        ImGui::SameLine();

        ImGui::PushID("Purchase List");
        if (ImGui::Button("..."))
            ImGui::OpenPopup("");

        if (ImGui::BeginPopup("")) {
            ImGui::SetNextItemWidth(75.0f);
            ImGui::Combo("Mode", &miscConfig.purchaseList.mode, "Details\0Summary\0");
            ImGui::Checkbox("Only During Freeze Time", &miscConfig.purchaseList.onlyDuringFreezeTime);
            ImGui::Checkbox("Show Prices", &miscConfig.purchaseList.showPrices);
            ImGui::Checkbox("No Title Bar", &miscConfig.purchaseList.noTitleBar);
            ImGui::EndPopup();
        }
        ImGui::PopID();

        ImGui::Checkbox("Reportbot", &miscConfig.reportbot.enabled);
        ImGui::SameLine();
        ImGui::PushID("Reportbot");

        if (ImGui::Button("..."))
            ImGui::OpenPopup("");

        if (ImGui::BeginPopup("")) {
            ImGui::PushItemWidth(80.0f);
            ImGui::Combo("Target", &miscConfig.reportbot.target, "Enemies\0Allies\0All\0");
            ImGui::InputInt("Delay (s)", &miscConfig.reportbot.delay);
            miscConfig.reportbot.delay = (std::max)(miscConfig.reportbot.delay, 1);
            ImGui::InputInt("Rounds", &miscConfig.reportbot.rounds);
            miscConfig.reportbot.rounds = (std::max)(miscConfig.reportbot.rounds, 1);
            ImGui::PopItemWidth();
            ImGui::Checkbox("Abusive Communications", &miscConfig.reportbot.textAbuse);
            ImGui::Checkbox("Griefing", &miscConfig.reportbot.griefing);
            ImGui::Checkbox("Wall Hacking", &miscConfig.reportbot.wallhack);
            ImGui::Checkbox("Aim Hacking", &miscConfig.reportbot.aimbot);
            ImGui::Checkbox("Other Hacking", &miscConfig.reportbot.other);
            if (ImGui::Button("Reset"))
                Misc::resetReportbot();
            ImGui::EndPopup();
        }
        ImGui::PopID();

        if (ImGui::Button("Unhook"))
            hooks->uninstall();

        ImGui::EndChild();
    }
    //visuals tab merge chams, streamproof esp, obj
    if (tabs == 4) {

        static int visualtab = 1;


        ImGui::SetCursorPos({ 155.f,26.f });

        ImGui::BeginChild("child0", { 541.f,366.f }, true);

        ImGui::SetCursorPos({ 3.f,3.f });
        if (ImGui::Button("chams", { 57.f,19.f }))
        {
            visualtab = 1;
        }
        ImGui::SetCursorPos({ 121.f,3.f });
        if (ImGui::Button("glow", { 57.f,19.f }))
        {
            visualtab = 2;
        }
        ImGui::SetCursorPos({ 62.f,3.f });
        if (ImGui::Button("esp", { 57.f,19.f }))
        {
            visualtab = 3;
        }
        ImGui::SetCursorPos({ 180.f,3.f });
        if (ImGui::Button("world", { 57.f,19.f }))
        {
            visualtab = 4;
        }


        ImGui::EndChild();

        if (visualtab == 1) {
            ImGui::SetCursorPos({ 164.f,48.f });
            ImGui::BeginChild("chams", { 524.f,336.f }, true);


            ImGui::hotkey("Toggle Key", config->chamsToggleKey, 80.0f);
            ImGui::hotkey("Hold Key", config->chamsHoldKey, 80.0f);
            ImGui::Separator();

            static int currentCategory{ 0 };
            ImGui::PushItemWidth(110.0f);
            ImGui::PushID(0);

            static int material = 1;

            if (ImGui::Combo("", &currentCategory, "Allies\0Enemies\0Planting\0Defusing\0Local player\0Weapons\0Hands\0Backtrack\0Sleeves\0"))
                material = 1;

            ImGui::PopID();

            ImGui::SameLine();

            if (material <= 1)
                ImGuiCustom::arrowButtonDisabled("##left", ImGuiDir_Left);
            else if (ImGui::ArrowButton("##left", ImGuiDir_Left))
                --material;

            ImGui::SameLine();
            ImGui::Text("%d", material);

            constexpr std::array categories{ "Allies", "Enemies", "Planting", "Defusing", "Local player", "Weapons", "Hands", "Backtrack", "Sleeves" };

            ImGui::SameLine();

            if (material >= int(config->chams[categories[currentCategory]].materials.size()))
                ImGuiCustom::arrowButtonDisabled("##right", ImGuiDir_Right);
            else if (ImGui::ArrowButton("##right", ImGuiDir_Right))
                ++material;

            ImGui::SameLine();

            auto& chams{ config->chams[categories[currentCategory]].materials[material - 1] };

            ImGui::Checkbox("Enabled", &chams.enabled);
            ImGui::Separator();
            ImGui::Checkbox("Health based", &chams.healthBased);
            ImGui::Checkbox("Blinking", &chams.blinking);
            ImGui::Combo("Material", &chams.material, "Normal\0Flat\0Animated\0Platinum\0Glass\0Chrome\0Crystal\0Silver\0Gold\0Plastic\0Glow\0Pearlescent\0Metallic\0");
            ImGui::Checkbox("Wireframe", &chams.wireframe);
            ImGui::Checkbox("Cover", &chams.cover);
            ImGui::Checkbox("Ignore-Z", &chams.ignorez);
            ImGuiCustom::colorPicker("Color", chams);




            ImGui::End();

        }

        if (visualtab == 2) {

            ImGui::SetCursorPos({ 164.f,48.f });

            ImGui::BeginChild("glow", { 524.f,336.f }, true);

            ImGui::hotkey("Toggle Key", glowToggleKey, 80.0f);
            ImGui::hotkey("Hold Key", glowHoldKey, 80.0f);
            ImGui::Separator();

            static int currentCategory{ 0 };
            ImGui::PushItemWidth(110.0f);
            ImGui::PushID(0);
            constexpr std::array categories{ "Allies", "Enemies", "Planting", "Defusing", "Local Player", "Weapons", "C4", "Planted C4", "Chickens", "Defuse Kits", "Projectiles", "Hostages", "Ragdolls" };
            ImGui::Combo("", &currentCategory, categories.data(), categories.size());
            ImGui::PopID();
            GlowItem* currentItem;
            if (currentCategory <= 3) {
                ImGui::SameLine();
                static int currentType{ 0 };
                ImGui::PushID(1);
                ImGui::Combo("", &currentType, "All\0Visible\0Occluded\0");
                ImGui::PopID();
                auto& cfg = playerGlowConfig[categories[currentCategory]];
                switch (currentType) {
                case 0: currentItem = &cfg.all; break;
                case 1: currentItem = &cfg.visible; break;
                case 2: currentItem = &cfg.occluded; break;
                }
            }
            else {
                currentItem = &glowConfig[categories[currentCategory]];
            }

            ImGui::SameLine();
            ImGui::Checkbox("Enabled", &currentItem->enabled);
            ImGui::Separator();
            ImGui::Columns(2, nullptr, false);
            ImGui::SetColumnOffset(1, 150.0f);
            ImGui::Checkbox("Health based", &currentItem->healthBased);

            ImGuiCustom::colorPicker("Color", *currentItem);

            ImGui::NextColumn();
            ImGui::SetNextItemWidth(100.0f);
            ImGui::Combo("Style", &currentItem->style, "Default\0Rim3d\0Edge\0Edge Pulse\0");

            ImGui::End();

        }
        if (visualtab == 3) {
            ImGui::SetCursorPos({ 164.f,48.f });
            ImGui::BeginChild("esp", { 524.f,336.f }, true);

            ImGui::hotkey("Toggle Key", config->streamProofESP.toggleKey, 80.0f);
            ImGui::hotkey("Hold Key", config->streamProofESP.holdKey, 80.0f);
            ImGui::Separator();

            static std::size_t currentCategory;
            static auto currentItem = "All";

            constexpr auto getConfigShared = [](std::size_t category, const char* item) noexcept -> Shared& {
                switch (category) {
                case 0: default: return config->streamProofESP.enemies[item];
                case 1: return config->streamProofESP.allies[item];
                case 2: return config->streamProofESP.weapons[item];
                case 3: return config->streamProofESP.projectiles[item];
                case 4: return config->streamProofESP.lootCrates[item];
                case 5: return config->streamProofESP.otherEntities[item];
                }
            };

            constexpr auto getConfigPlayer = [](std::size_t category, const char* item) noexcept -> Player& {
                switch (category) {
                case 0: default: return config->streamProofESP.enemies[item];
                case 1: return config->streamProofESP.allies[item];
                }
            };

            if (ImGui::BeginListBox("##list", { 170.0f, 300.0f })) {
                constexpr std::array categories{ "Enemies", "Allies", "Weapons", "Projectiles", "Loot Crates", "Other Entities" };

                for (std::size_t i = 0; i < categories.size(); ++i) {
                    if (ImGui::Selectable(categories[i], currentCategory == i && std::string_view{ currentItem } == "All")) {
                        currentCategory = i;
                        currentItem = "All";
                    }

                    if (ImGui::BeginDragDropSource()) {
                        switch (i) {
                        case 0: case 1: ImGui::SetDragDropPayload("Player", &getConfigPlayer(i, "All"), sizeof(Player), ImGuiCond_Once); break;
                        case 2: ImGui::SetDragDropPayload("Weapon", &config->streamProofESP.weapons["All"], sizeof(Weapon), ImGuiCond_Once); break;
                        case 3: ImGui::SetDragDropPayload("Projectile", &config->streamProofESP.projectiles["All"], sizeof(Projectile), ImGuiCond_Once); break;
                        default: ImGui::SetDragDropPayload("Entity", &getConfigShared(i, "All"), sizeof(Shared), ImGuiCond_Once); break;
                        }
                        ImGui::EndDragDropSource();
                    }

                    if (ImGui::BeginDragDropTarget()) {
                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Player")) {
                            const auto& data = *(Player*)payload->Data;

                            switch (i) {
                            case 0: case 1: getConfigPlayer(i, "All") = data; break;
                            case 2: config->streamProofESP.weapons["All"] = data; break;
                            case 3: config->streamProofESP.projectiles["All"] = data; break;
                            default: getConfigShared(i, "All") = data; break;
                            }
                        }

                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Weapon")) {
                            const auto& data = *(Weapon*)payload->Data;

                            switch (i) {
                            case 0: case 1: getConfigPlayer(i, "All") = data; break;
                            case 2: config->streamProofESP.weapons["All"] = data; break;
                            case 3: config->streamProofESP.projectiles["All"] = data; break;
                            default: getConfigShared(i, "All") = data; break;
                            }
                        }

                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Projectile")) {
                            const auto& data = *(Projectile*)payload->Data;

                            switch (i) {
                            case 0: case 1: getConfigPlayer(i, "All") = data; break;
                            case 2: config->streamProofESP.weapons["All"] = data; break;
                            case 3: config->streamProofESP.projectiles["All"] = data; break;
                            default: getConfigShared(i, "All") = data; break;
                            }
                        }

                        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Entity")) {
                            const auto& data = *(Shared*)payload->Data;

                            switch (i) {
                            case 0: case 1: getConfigPlayer(i, "All") = data; break;
                            case 2: config->streamProofESP.weapons["All"] = data; break;
                            case 3: config->streamProofESP.projectiles["All"] = data; break;
                            default: getConfigShared(i, "All") = data; break;
                            }
                        }
                        ImGui::EndDragDropTarget();
                    }

                    ImGui::PushID(i);
                    ImGui::Indent();

                    const auto items = [](std::size_t category) noexcept -> std::vector<const char*> {
                        switch (category) {
                        case 0:
                        case 1: return { "Visible", "Occluded" };
                        case 2: return { "Pistols", "SMGs", "Rifles", "Sniper Rifles", "Shotguns", "Machineguns", "Grenades", "Melee", "Other" };
                        case 3: return { "Flashbang", "HE Grenade", "Breach Charge", "Bump Mine", "Decoy Grenade", "Molotov", "TA Grenade", "Smoke Grenade", "Snowball" };
                        case 4: return { "Pistol Case", "Light Case", "Heavy Case", "Explosive Case", "Tools Case", "Cash Dufflebag" };
                        case 5: return { "Defuse Kit", "Chicken", "Planted C4", "Hostage", "Sentry", "Cash", "Ammo Box", "Radar Jammer", "Snowball Pile", "Collectable Coin" };
                        default: return { };
                        }
                    }(i);

                    const auto categoryEnabled = getConfigShared(i, "All").enabled;

                    for (std::size_t j = 0; j < items.size(); ++j) {
                        static bool selectedSubItem;
                        if (!categoryEnabled || getConfigShared(i, items[j]).enabled) {
                            if (ImGui::Selectable(items[j], currentCategory == i && !selectedSubItem && std::string_view{ currentItem } == items[j])) {
                                currentCategory = i;
                                currentItem = items[j];
                                selectedSubItem = false;
                            }

                            if (ImGui::BeginDragDropSource()) {
                                switch (i) {
                                case 0: case 1: ImGui::SetDragDropPayload("Player", &getConfigPlayer(i, items[j]), sizeof(Player), ImGuiCond_Once); break;
                                case 2: ImGui::SetDragDropPayload("Weapon", &config->streamProofESP.weapons[items[j]], sizeof(Weapon), ImGuiCond_Once); break;
                                case 3: ImGui::SetDragDropPayload("Projectile", &config->streamProofESP.projectiles[items[j]], sizeof(Projectile), ImGuiCond_Once); break;
                                default: ImGui::SetDragDropPayload("Entity", &getConfigShared(i, items[j]), sizeof(Shared), ImGuiCond_Once); break;
                                }
                                ImGui::EndDragDropSource();
                            }

                            if (ImGui::BeginDragDropTarget()) {
                                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Player")) {
                                    const auto& data = *(Player*)payload->Data;

                                    switch (i) {
                                    case 0: case 1: getConfigPlayer(i, items[j]) = data; break;
                                    case 2: config->streamProofESP.weapons[items[j]] = data; break;
                                    case 3: config->streamProofESP.projectiles[items[j]] = data; break;
                                    default: getConfigShared(i, items[j]) = data; break;
                                    }
                                }

                                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Weapon")) {
                                    const auto& data = *(Weapon*)payload->Data;

                                    switch (i) {
                                    case 0: case 1: getConfigPlayer(i, items[j]) = data; break;
                                    case 2: config->streamProofESP.weapons[items[j]] = data; break;
                                    case 3: config->streamProofESP.projectiles[items[j]] = data; break;
                                    default: getConfigShared(i, items[j]) = data; break;
                                    }
                                }

                                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Projectile")) {
                                    const auto& data = *(Projectile*)payload->Data;

                                    switch (i) {
                                    case 0: case 1: getConfigPlayer(i, items[j]) = data; break;
                                    case 2: config->streamProofESP.weapons[items[j]] = data; break;
                                    case 3: config->streamProofESP.projectiles[items[j]] = data; break;
                                    default: getConfigShared(i, items[j]) = data; break;
                                    }
                                }

                                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Entity")) {
                                    const auto& data = *(Shared*)payload->Data;

                                    switch (i) {
                                    case 0: case 1: getConfigPlayer(i, items[j]) = data; break;
                                    case 2: config->streamProofESP.weapons[items[j]] = data; break;
                                    case 3: config->streamProofESP.projectiles[items[j]] = data; break;
                                    default: getConfigShared(i, items[j]) = data; break;
                                    }
                                }
                                ImGui::EndDragDropTarget();
                            }
                        }

                        if (i != 2)
                            continue;

                        ImGui::Indent();

                        const auto subItems = [](std::size_t item) noexcept -> std::vector<const char*> {
                            switch (item) {
                            case 0: return { "Glock-18", "P2000", "USP-S", "Dual Berettas", "P250", "Tec-9", "Five-SeveN", "CZ75-Auto", "Desert Eagle", "R8 Revolver" };
                            case 1: return { "MAC-10", "MP9", "MP7", "MP5-SD", "UMP-45", "P90", "PP-Bizon" };
                            case 2: return { "Galil AR", "FAMAS", "AK-47", "M4A4", "M4A1-S", "SG 553", "AUG" };
                            case 3: return { "SSG 08", "AWP", "G3SG1", "SCAR-20" };
                            case 4: return { "Nova", "XM1014", "Sawed-Off", "MAG-7" };
                            case 5: return { "M249", "Negev" };
                            case 6: return { "Flashbang", "HE Grenade", "Smoke Grenade", "Molotov", "Decoy Grenade", "Incendiary", "TA Grenade", "Fire Bomb", "Diversion", "Frag Grenade", "Snowball" };
                            case 7: return { "Axe", "Hammer", "Wrench" };
                            case 8: return { "C4", "Healthshot", "Bump Mine", "Zone Repulsor", "Shield" };
                            default: return { };
                            }
                        }(j);

                        const auto itemEnabled = getConfigShared(i, items[j]).enabled;

                        for (const auto subItem : subItems) {
                            auto& subItemConfig = config->streamProofESP.weapons[subItem];
                            if ((categoryEnabled || itemEnabled) && !subItemConfig.enabled)
                                continue;

                            if (ImGui::Selectable(subItem, currentCategory == i && selectedSubItem && std::string_view{ currentItem } == subItem)) {
                                currentCategory = i;
                                currentItem = subItem;
                                selectedSubItem = true;
                            }

                            if (ImGui::BeginDragDropSource()) {
                                ImGui::SetDragDropPayload("Weapon", &subItemConfig, sizeof(Weapon), ImGuiCond_Once);
                                ImGui::EndDragDropSource();
                            }

                            if (ImGui::BeginDragDropTarget()) {
                                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Player")) {
                                    const auto& data = *(Player*)payload->Data;
                                    subItemConfig = data;
                                }

                                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Weapon")) {
                                    const auto& data = *(Weapon*)payload->Data;
                                    subItemConfig = data;
                                }

                                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Projectile")) {
                                    const auto& data = *(Projectile*)payload->Data;
                                    subItemConfig = data;
                                }

                                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Entity")) {
                                    const auto& data = *(Shared*)payload->Data;
                                    subItemConfig = data;
                                }
                                ImGui::EndDragDropTarget();
                            }
                        }

                        ImGui::Unindent();
                    }
                    ImGui::Unindent();
                    ImGui::PopID();
                }
                ImGui::EndListBox();
            }

            ImGui::SameLine();

            if (ImGui::BeginChild("##child", { 400.0f, 0.0f })) {
                auto& sharedConfig = getConfigShared(currentCategory, currentItem);

                ImGui::Checkbox("Enabled", &sharedConfig.enabled);
                ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 260.0f);
                ImGui::SetNextItemWidth(220.0f);
                if (ImGui::BeginCombo("Font", config->getSystemFonts()[sharedConfig.font.index].c_str())) {
                    for (size_t i = 0; i < config->getSystemFonts().size(); i++) {
                        bool isSelected = config->getSystemFonts()[i] == sharedConfig.font.name;
                        if (ImGui::Selectable(config->getSystemFonts()[i].c_str(), isSelected, 0, { 250.0f, 0.0f })) {
                            sharedConfig.font.index = i;
                            sharedConfig.font.name = config->getSystemFonts()[i];
                            config->scheduleFontLoad(sharedConfig.font.name);
                        }
                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

                ImGui::Separator();

                constexpr auto spacing = 250.0f;
                ImGuiCustom::colorPicker("Snapline", sharedConfig.snapline);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(90.0f);
                ImGui::Combo("##1", &sharedConfig.snapline.type, "Bottom\0Top\0Crosshair\0");
                ImGui::SameLine(spacing);
                ImGuiCustom::colorPicker("Box", sharedConfig.box);
                ImGui::SameLine();

                ImGui::PushID("Box");

                if (ImGui::Button("..."))
                    ImGui::OpenPopup("");

                if (ImGui::BeginPopup("")) {
                    ImGui::SetNextItemWidth(95.0f);
                    ImGui::Combo("Type", &sharedConfig.box.type, "2D\0" "2D corners\0" "3D\0" "3D corners\0");
                    ImGui::SetNextItemWidth(275.0f);
                    ImGui::SliderFloat3("Scale", sharedConfig.box.scale.data(), 0.0f, 0.50f, "%.2f");
                    ImGuiCustom::colorPicker("Fill", sharedConfig.box.fill);
                    ImGui::EndPopup();
                }

                ImGui::PopID();

                ImGuiCustom::colorPicker("Name", sharedConfig.name);
                ImGui::SameLine(spacing);

                if (currentCategory < 2) {
                    auto& playerConfig = getConfigPlayer(currentCategory, currentItem);

                    ImGuiCustom::colorPicker("Weapon", playerConfig.weapon);
                    ImGuiCustom::colorPicker("Flash Duration", playerConfig.flashDuration);
                    ImGui::SameLine(spacing);
                    ImGuiCustom::colorPicker("Skeleton", playerConfig.skeleton);
                    ImGui::Checkbox("Audible Only", &playerConfig.audibleOnly);
                    ImGui::SameLine(spacing);
                    ImGui::Checkbox("Spotted Only", &playerConfig.spottedOnly);

                    ImGuiCustom::colorPicker("Head Box", playerConfig.headBox);
                    ImGui::SameLine();

                    ImGui::PushID("Head Box");

                    if (ImGui::Button("..."))
                        ImGui::OpenPopup("");

                    if (ImGui::BeginPopup("")) {
                        ImGui::SetNextItemWidth(95.0f);
                        ImGui::Combo("Type", &playerConfig.headBox.type, "2D\0" "2D corners\0" "3D\0" "3D corners\0");
                        ImGui::SetNextItemWidth(275.0f);
                        ImGui::SliderFloat3("Scale", playerConfig.headBox.scale.data(), 0.0f, 0.50f, "%.2f");
                        ImGuiCustom::colorPicker("Fill", playerConfig.headBox.fill);
                        ImGui::EndPopup();
                    }

                    ImGui::PopID();

                    ImGui::SameLine(spacing);
                    ImGui::Checkbox("Health Bar", &playerConfig.healthBar.enabled);
                    ImGui::SameLine();

                    ImGui::PushID("Health Bar");

                    if (ImGui::Button("..."))
                        ImGui::OpenPopup("");

                    if (ImGui::BeginPopup("")) {
                        ImGui::SetNextItemWidth(95.0f);
                        ImGui::Combo("Type", &playerConfig.healthBar.type, "Gradient\0Solid\0Health-based\0");
                        if (playerConfig.healthBar.type == HealthBar::Solid) {
                            ImGui::SameLine();
                            ImGuiCustom::colorPicker("", playerConfig.healthBar.asColor4());
                        }
                        ImGui::EndPopup();
                    }

                    ImGui::PopID();
                }
                else if (currentCategory == 2) {
                    auto& weaponConfig = config->streamProofESP.weapons[currentItem];
                    ImGuiCustom::colorPicker("Ammo", weaponConfig.ammo);
                }
                else if (currentCategory == 3) {
                    auto& trails = config->streamProofESP.projectiles[currentItem].trails;

                    ImGui::Checkbox("Trails", &trails.enabled);
                    ImGui::SameLine(spacing + 77.0f);
                    ImGui::PushID("Trails");

                    if (ImGui::Button("..."))
                        ImGui::OpenPopup("");

                    if (ImGui::BeginPopup("")) {
                        constexpr auto trailPicker = [](const char* name, Trail& trail) noexcept {
                            ImGui::PushID(name);
                            ImGuiCustom::colorPicker(name, trail);
                            ImGui::SameLine(150.0f);
                            ImGui::SetNextItemWidth(95.0f);
                            ImGui::Combo("", &trail.type, "Line\0Circles\0Filled Circles\0");
                            ImGui::SameLine();
                            ImGui::SetNextItemWidth(95.0f);
                            ImGui::InputFloat("Time", &trail.time, 0.1f, 0.5f, "%.1fs");
                            trail.time = std::clamp(trail.time, 1.0f, 60.0f);
                            ImGui::PopID();
                        };

                        trailPicker("Local Player", trails.localPlayer);
                        trailPicker("Allies", trails.allies);
                        trailPicker("Enemies", trails.enemies);
                        ImGui::EndPopup();
                    }

                    ImGui::PopID();
                }

                ImGui::SetNextItemWidth(95.0f);
                ImGui::InputFloat("Text Cull Distance", &sharedConfig.textCullDistance, 0.4f, 0.8f, "%.1fm");
                sharedConfig.textCullDistance = std::clamp(sharedConfig.textCullDistance, 0.0f, 999.9f);
            }



            ImGui::End();
        }
        if (visualtab == 4) {
            ImGui::SetCursorPos({ 164.f,48.f });
            ImGui::BeginChild("world", { 524.f,336.f }, true);


            ImGui::Columns(2, nullptr, false);
            ImGui::SetColumnOffset(1, 280.0f);
            ImGui::Checkbox("Disable post-processing", &visualsConfig.disablePostProcessing);
            ImGui::Checkbox("Inverse ragdoll gravity", &visualsConfig.inverseRagdollGravity);
            ImGui::Checkbox("No fog", &visualsConfig.noFog);
            ImGui::Checkbox("No 3d sky", &visualsConfig.no3dSky);
            ImGui::Checkbox("No aim punch", &visualsConfig.noAimPunch);
            ImGui::Checkbox("No view punch", &visualsConfig.noViewPunch);
            ImGui::Checkbox("No hands", &visualsConfig.noHands);
            ImGui::Checkbox("No sleeves", &visualsConfig.noSleeves);
            ImGui::Checkbox("No weapons", &visualsConfig.noWeapons);
            ImGui::Checkbox("No smoke", &visualsConfig.noSmoke);
            ImGui::Checkbox("No blur", &visualsConfig.noBlur);
            ImGui::Checkbox("No scope overlay", &visualsConfig.noScopeOverlay);
            ImGui::Checkbox("No grass", &visualsConfig.noGrass);
            ImGui::Checkbox("No shadows", &visualsConfig.noShadows);
            ImGui::Checkbox("Wireframe smoke", &visualsConfig.wireframeSmoke);
            ImGui::NextColumn();
            ImGui::Checkbox("Zoom", &visualsConfig.zoom);
            ImGui::SameLine();
            ImGui::PushID("Zoom Key");
            ImGui::hotkey("", visualsConfig.zoomKey);
            ImGui::PopID();
            ImGui::Checkbox("Thirdperson", &visualsConfig.thirdperson);
            ImGui::SameLine();
            ImGui::PushID("Thirdperson Key");
            ImGui::hotkey("", visualsConfig.thirdpersonKey);
            ImGui::PopID();
            ImGui::PushItemWidth(290.0f);
            ImGui::PushID(0);
            ImGui::SliderInt("", &visualsConfig.thirdpersonDistance, 0, 1000, "Thirdperson distance: %d");
            ImGui::PopID();
            ImGui::PushID(1);
            ImGui::SliderInt("", &visualsConfig.viewmodelFov, -60, 60, "Viewmodel FOV: %d");
            ImGui::PopID();
            ImGui::PushID(2);
            ImGui::SliderInt("", &visualsConfig.fov, -60, 60, "FOV: %d");
            ImGui::PopID();
            ImGui::PushID(3);
            ImGui::SliderInt("", &visualsConfig.farZ, 0, 2000, "Far Z: %d");
            ImGui::PopID();
            ImGui::PushID(4);
            ImGui::SliderInt("", &visualsConfig.flashReduction, 0, 100, "Flash reduction: %d%%");
            ImGui::PopID();
            ImGui::PushID(5);
            ImGui::SliderFloat("", &visualsConfig.brightness, 0.0f, 1.0f, "Brightness: %.2f");
            ImGui::PopID();
            ImGui::PopItemWidth();
            ImGui::Combo("Skybox", &visualsConfig.skybox, Visuals::skyboxList.data(), Visuals::skyboxList.size());
            ImGuiCustom::colorPicker("World color", visualsConfig.world);
            ImGuiCustom::colorPicker("Sky color", visualsConfig.sky);
            ImGui::Checkbox("Deagle spinner", &visualsConfig.deagleSpinner);
            ImGui::Combo("Screen effect", &visualsConfig.screenEffect, "None\0Drone cam\0Drone cam with noise\0Underwater\0Healthboost\0Dangerzone\0");
            ImGui::Combo("Hit effect", &visualsConfig.hitEffect, "None\0Drone cam\0Drone cam with noise\0Underwater\0Healthboost\0Dangerzone\0");
            ImGui::SliderFloat("Hit effect time", &visualsConfig.hitEffectTime, 0.1f, 1.5f, "%.2fs");
            ImGui::Combo("Hit marker", &visualsConfig.hitMarker, "None\0Default (Cross)\0");
            ImGui::SliderFloat("Hit marker time", &visualsConfig.hitMarkerTime, 0.1f, 1.5f, "%.2fs");
            ImGuiCustom::colorPicker("Bullet Tracers", visualsConfig.bulletTracers.asColor4().color.data(), &visualsConfig.bulletTracers.asColor4().color[3], nullptr, nullptr, &visualsConfig.bulletTracers.enabled);
            ImGuiCustom::colorPicker("Molotov Hull", visualsConfig.molotovHull);

            ImGui::Checkbox("Color correction", &visualsConfig.colorCorrection.enabled);
            ImGui::SameLine();

            if (bool ccPopup = ImGui::Button("Edit"))
                ImGui::OpenPopup("##popup");

            if (ImGui::BeginPopup("##popup")) {
                ImGui::VSliderFloat("##1", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.blue, 0.0f, 1.0f, "Blue\n%.3f"); ImGui::SameLine();
                ImGui::VSliderFloat("##2", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.red, 0.0f, 1.0f, "Red\n%.3f"); ImGui::SameLine();
                ImGui::VSliderFloat("##3", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.mono, 0.0f, 1.0f, "Mono\n%.3f"); ImGui::SameLine();
                ImGui::VSliderFloat("##4", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.saturation, 0.0f, 1.0f, "Sat\n%.3f"); ImGui::SameLine();
                ImGui::VSliderFloat("##5", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.ghost, 0.0f, 1.0f, "Ghost\n%.3f"); ImGui::SameLine();
                ImGui::VSliderFloat("##6", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.green, 0.0f, 1.0f, "Green\n%.3f"); ImGui::SameLine();
                ImGui::VSliderFloat("##7", { 40.0f, 160.0f }, &visualsConfig.colorCorrection.yellow, 0.0f, 1.0f, "Yellow\n%.3f"); ImGui::SameLine();
                ImGui::EndPopup();
            }
            ImGui::Columns(1);



            ImGui::End();
        }


        ImGui::EndChild();
    }
    //skins, complete
    if (tabs == 5) {
        ImGui::SetCursorPos({ 158.f,28.f });

        ImGui::BeginChild("child0", { 535.f,365.f }, true);
        static std::string filter;

        static bool isInAddMode = false;


        if (ImGui::Button("Add items..")) {
            isInAddMode = true;
        }
        if (!isInAddMode) {

            if (ImGui::Button("Force Update"))
                InventoryChanger::scheduleHudUpdate();
        }

        constexpr auto rarityColor = [](int rarity) noexcept {
            constexpr auto rarityColors = std::to_array<ImU32>({
                IM_COL32(106,  97,  85, 255),
                IM_COL32(176, 195, 217, 255),
                IM_COL32(94, 152, 217, 255),
                IM_COL32(75, 105, 255, 255),
                IM_COL32(136,  71, 255, 255),
                IM_COL32(211,  44, 230, 255),
                IM_COL32(235,  75,  75, 255),
                IM_COL32(228, 174,  57, 255)
                });
            return rarityColors[static_cast<std::size_t>(rarity) < rarityColors.size() ? rarity : 0];
        };

        if (isInAddMode) {
            static std::unordered_map<StaticData::ItemIndex, int> selectedToAdd;
            static std::vector<StaticData::ItemIndex> toAddOrder;
            if (ImGui::Button("Back")) {
                isInAddMode = false;
                selectedToAdd.clear();
                toAddOrder.clear();
            }
            ImGui::SameLine();
            const auto canAdd = !selectedToAdd.empty();
            if (!canAdd) {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
            }
            if (ImGui::Button(("Add selected (" + std::to_string(selectedToAdd.size()) + ")").c_str())) {
                isInAddMode = false;
                addToInventory(selectedToAdd, toAddOrder);
                selectedToAdd.clear();
                toAddOrder.clear();
            }
            if (!canAdd) {
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();
            }
            ImGui::SameLine();
            ImGui::SetNextItemWidth(-1.0f);
            ImGui::InputTextWithHint("##search", "Search weapon skins, stickers, knives, gloves, music kits..", &filter);

            constexpr auto passesFilter = [](const std::wstring& str, std::wstring filter) {
                constexpr auto delimiter = L" ";
                wchar_t* _;
                wchar_t* token = std::wcstok(filter.data(), delimiter, &_);
                while (token) {
                    if (!std::wcsstr(str.c_str(), token))
                        return false;
                    token = std::wcstok(nullptr, delimiter, &_);
                }
                return true;
            };
            if (ImGui::BeginChild("##scrollarea", ImVec2{ 0.0f, 400.0f })) {
                const auto& gameItems = StaticData::gameItems();
                const std::wstring filterWide = Helpers::toUpper(Helpers::toWideString(filter));
                for (std::size_t i = 0; i < gameItems.size(); ++i) {
                    if (!filter.empty() && !passesFilter(std::wstring(StaticData::getWeaponNameUpper(gameItems[i].weaponID)), filterWide) && (!gameItems[i].hasPaintKit() || !passesFilter(StaticData::paintKits()[gameItems[i].dataIndex].nameUpperCase, filterWide)))
                        continue;
                    ImGui::PushID(i);

                    const auto selected = selectedToAdd.contains(i);

                    if (const auto toAddCount = selected ? &selectedToAdd[i] : nullptr; ImGui::SkinSelectable(gameItems[i], { 37.0f, 28.0f }, { 200.0f, 150.0f }, rarityColor(gameItems[i].rarity), selected, toAddCount)) {
                        if (selected) {
                            selectedToAdd.erase(i);
                            std::erase(toAddOrder, i);
                        }
                        else {
                            selectedToAdd.emplace(i, 1);
                            toAddOrder.push_back(i);
                        }
                    }
                    ImGui::PopID();
                }
            }
            ImGui::EndChild();
        }
        else {
            if (ImGui::BeginChild("##scrollarea2", ImVec2{ 0.0f, 400.0f })) {
                auto& inventory = Inventory::get();
                for (std::size_t i = inventory.size(); i-- > 0;) {
                    if (inventory[i].isDeleted() || inventory[i].shouldDelete())
                        continue;

                    ImGui::PushID(i);
                    bool shouldDelete = false;
                    ImGui::SkinItem(inventory[i].get(), { 37.0f, 28.0f }, { 200.0f, 150.0f }, rarityColor(inventory[i].get().rarity), shouldDelete);
                    if (shouldDelete)
                        inventory[i].markToDelete();
                    ImGui::PopID();
                }
            }
            ImGui::EndChild();
        }




        if (tabs == 6) {

        }


    }
    //settings
    if (tabs == 6) {
        ImGui::SetCursorPos({ 158.f,20.f });

        ImGui::BeginChild("child0", { 535.f,375.f }, true);

        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnOffset(1, 170.0f);

        static bool incrementalLoad = false;
        ImGui::Checkbox("Incremental Load", &incrementalLoad);

        ImGui::PushItemWidth(160.0f);

        auto& configItems = config->getConfigs();
        static int currentConfig = -1;

        static std::u8string buffer;

        timeToNextConfigRefresh -= ImGui::GetIO().DeltaTime;
        if (timeToNextConfigRefresh <= 0.0f) {
            config->listConfigs();
            if (const auto it = std::find(configItems.begin(), configItems.end(), buffer); it != configItems.end())
                currentConfig = std::distance(configItems.begin(), it);
            timeToNextConfigRefresh = 0.1f;
        }

        if (static_cast<std::size_t>(currentConfig) >= configItems.size())
            currentConfig = -1;

        if (ImGui::ListBox("", &currentConfig, [](void* data, int idx, const char** out_text) {
            auto& vector = *static_cast<std::vector<std::u8string>*>(data);
            *out_text = (const char*)vector[idx].c_str();
            return true;
            }, &configItems, configItems.size(), 5) && currentConfig != -1)
            buffer = configItems[currentConfig];

            ImGui::PushID(0);
            if (ImGui::InputTextWithHint("", "config name", &buffer, ImGuiInputTextFlags_EnterReturnsTrue)) {
                if (currentConfig != -1)
                    config->rename(currentConfig, buffer);
            }
            ImGui::PopID();
            ImGui::NextColumn();

            ImGui::PushItemWidth(100.0f);

            if (ImGui::Button("Open config directory"))
                config->openConfigDir();

            if (ImGui::Button("Create config", { 100.0f, 25.0f }))
                config->add(buffer.c_str());

            if (ImGui::Button("Reset config", { 100.0f, 25.0f }))
                ImGui::OpenPopup("Config to reset");

            if (ImGui::BeginPopup("Config to reset")) {
                static constexpr const char* names[]{ "Whole", "Aimbot", "Triggerbot", "Backtrack", "Anti aim", "Glow", "Chams", "ESP", "Visuals", "Inventory Changer", "Sound", "Style", "Misc" };
                for (int i = 0; i < IM_ARRAYSIZE(names); i++) {
                    if (i == 1) ImGui::Separator();

                    if (ImGui::Selectable(names[i])) {
                        switch (i) {
                        case 0: config->reset(); updateColors(); Misc::updateClanTag(true); InventoryChanger::scheduleHudUpdate(); break;
                        case 1: config->aimbot = { }; break;
                        case 2: config->triggerbot = { }; break;
                        case 3: Backtrack::resetConfig(); break;
                        case 4: AntiAim::resetConfig(); break;
                        case 5: Glow::resetConfig(); break;
                        case 6: config->chams = { }; break;
                        case 7: config->streamProofESP = { }; break;
                        case 8: Visuals::resetConfig(); break;
                        case 9: InventoryChanger::resetConfig(); InventoryChanger::scheduleHudUpdate(); break;
                        case 10: Sound::resetConfig(); break;
                        case 11: config->style = { }; updateColors(); break;
                        case 12: Misc::resetConfig(); Misc::updateClanTag(true); break;
                        }
                    }
                }
                ImGui::EndPopup();
            }
            if (currentConfig != -1) {
                if (ImGui::Button("Load selected", { 100.0f, 25.0f })) {
                    config->load(currentConfig, incrementalLoad);
                    updateColors();
                    InventoryChanger::scheduleHudUpdate();
                    Misc::updateClanTag(true);
                }
                if (ImGui::Button("Save selected", { 100.0f, 25.0f }))
                    config->save(currentConfig);
                if (ImGui::Button("Delete selected", { 100.0f, 25.0f })) {
                    config->remove(currentConfig);

                    if (static_cast<std::size_t>(currentConfig) < configItems.size())
                        buffer = configItems[currentConfig];
                    else
                        buffer.clear();
                }
            }
            ImGui::Columns(1);
            ImGui::EndChild();
    }
    //read section for future updates.
    if (tabs == 7) {
        ImGui::SetCursorPos({ 158.f,20.f });

        ImGui::BeginChild("child0", { 535.f,375.f }, true);


        ImGui::EndChild();
    }

}