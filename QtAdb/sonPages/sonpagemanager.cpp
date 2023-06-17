#include "sonpagemanager.h"

sonPageManager::sonPageManager()
{
    process = new adbProcess();
    explainer = new textExplainer();
}

sonPageManager::~sonPageManager()
{
    //delete process;
    //delete explainer;
}

animationWidget* sonPageManager::selector(QWidget *parent , QString parentName, int key, device dev)
{
    if(parentName == "devInfo")
    {
        //qDebug() << "dev.addr=" << dev.addr;
        return createSonPageFor_devInfo(parent, key , dev);
        //return createSonPageFor_activator(parent);
    }
    else if(parentName == "activator")
    {
        return createSonPageFor_activator(parent, key , dev);
    }
    else if(parentName == "apps")
    {
        return createSonPageFor_apps(parent, key , dev);
    }
    else if(parentName == "devControl")
    {
        return createSonPageFor_devControl(parent, key , dev);
    }
    else if(parentName == "recovery")
    {
        return createSonPageFor_recovery(parent, key , dev);
    }
    else if(parentName == "advanced")
    {
        return createSonPageFor_advanced(parent, key , dev);
    }

    throw "failed to create sonPage!";
    return NULL;
}

animationWidget* sonPageManager::createSonPageFor_devInfo(QWidget *parent, int key, device dev)
{
    switch(key +1)
    {
    case 2:
    {
        sp_wmsize *page = new sp_wmsize(parent);
        page->setDev(dev);
        return page;
    }

    case 3:
    {
        sp_dpiChanger *page = new sp_dpiChanger(parent);
        page->setDev(dev);
        return page;
    }
        break;
    }
    return NULL;
}

animationWidget* sonPageManager::createSonPageFor_activator(QWidget *parent, int key, device dev)
{
    //sp_activator *page = new sp_activator(parent);
    //return page;
    switch(key + 1)
    {
    case 1 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/brevent.png);",
                    "激活 黑阈",
                    "黑阈™不需要 root 也不需要解锁，能有效防止恶意应用在后台运行，从而让手机流畅省电。\n"
                    "黑阈主要采取以下手段来限制应用后台：\n"
                    "1. 停用状态。应用处于停用状态时，不会收到 Android 系统及 GMS 发送的广播，从而避免“被动运行”。\n"
                    "2. 待机。待机以后，应用无法访问网络，执行任务与同步等。这减少Android 系统被动运行该应用，同时即使运行也减少其网络活动。\n",
                    "adb -d shell sh /data/data/me.piebridge.brevent/brevent.sh");
        return page;
        break;
    }
    case 2  :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/icebox.png);",
                    "激活 冰箱 - 设备管理员",
                    "使用**设备管理器**模式激活冰箱前，请按下列步骤操作：\n"
                    "1. 确保手机上已安装冰箱，删除屏幕锁，索尼手机取出 SIM 卡，MIUI 开启「USB 调试（安全设置）」并关闭「MIUI 优化」\n"
                    "2. **请退出所有帐号**，如小米帐号、华为帐号、Google 帐号等，激活后可以再重新登录。可前往QtAdb的[其它] -> [帐户]查看并删除账号。\n"
                    "3. **请删除所有用户**，包括手机分身等，可前往QtAdb的[软件包管理器] -> [用户]中查看现有用户。\n",
                    "adb shell dpm set-device-owner com.catchingnow.icebox/.receiver.DPMReceiver");
        return page;
        break;
    }
    case 3 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/icebox.png);",
                    "激活 冰箱 - 普通模式",
                    "如果您未能成功配置设备管理员模式的冰箱，则可以考虑使用普通 ADB 模式。\n"
                    "- 优点：无需删除帐号等复杂步骤，直接使用\n"
                    "- 缺点：每次重启手机后必须要重新激活，否则无法冻结解冻 App\n"
                    "- 激活后需保持 USB 调试始终打开，设置 USB 连接设置为「仅充电」（MIUI 需开启「USB 调试（安全设置）」）\n",
                    "adb shell sh /sdcard/Android/data/com.catchingnow.icebox/files/start.sh");
        return page;
        break;
    }
    case 4 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/blackroom.png);", "激活 小黑屋 - 设备管理员",
                    "使用**设备管理器**模式激活小黑屋前，注意以下事项：\n"
                    "1. 打开手机开发者选项与 USB 调试，将 USB 连接设置为「仅充电」（小米手机需开启开发者选项「USB 调试（安全设置）」）。\n"
                    "2. **请退出所有帐号**，如小米帐号、华为帐号、Google 帐号等，激活后可以再重新登录。可前往QtAdb的[其它] -> [帐户]查看并删除账号。\n"
                    "3. **请删除所有用户**，包括手机分身等，可前往QtAdb的[软件包管理器] -> [用户]中查看现有用户。\n",
                    "adb shell dpm set-device-owner web1n.stopapp/.receiver.AdminReceiver");
        return page;
        break;
    }
    case 5 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/blackroom.png);",
                    "激活 小黑屋 - 麦克斯韦妖",
                    "麦克斯韦妖是小黑屋的一款冻结模式。借助它，小黑屋可以免 Root 权限冻结应用程序。  \n"
                    "麦克斯韦妖引擎与 ROM 的兼容性很好，不会出现设备管理员模式与 ROM 之间的一些兼容性问题。  \n"
                    "**麦克斯韦妖优点**  \n"
                    "- 无需移除账号与用户等操作，激活成功率极高。  \n"
                    "- 冻结速度快，点击即冻结。  \n\n"
                    "**麦克斯韦妖缺点**  \n"
                    "- 关机后即失效，因此每次开机需要重新激活。若不重新激活将无法打开已冻结 app。  \n",
                    "adb shell sh /storage/emulated/0/Android/data/web1n.stopapp/files/starter.sh");
        return page;
        break;
    }
    case 6 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/shizuku.png);", "激活 Shizuku",
                    "Android 11 及以上支持无线调试，您可以直接在设备上启动 Shizuku。  \n"
                    "对于未 root 设备，则需要借助 adb 启动。  \n"
                    "**请注意**  \n"
                    "- 设备重新启动后需要再次连接电脑。  \n"
                    "在一些定制系统上 Shizuku 可能会随机停止，此时:  \n\n"
                    "- 不要关闭“USB 调试”及“开发者选项”  \n"
                    "- 保证在连接电脑期间 USB 使用模式不变。通常的做法是在“开发者选项”中将 USB 使用模式改为“仅充电”  \n"
                    "- 连接 USB 后，若弹出类似“是否允许访问文件”的对话框，请不要点击它，因为点击后 USB 使用模式会发生变化。  \n"
                    "- Sony 设备不要点击连接 USB 后弹出的对话框。  \n",
                    "adb shell sh /sdcard/Android/data/moe.shizuku.privileged.api/start.sh");
        return page;
        break;
    }
    case 7 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/blackhole.png);", "激活 黑洞",
                    "**黑洞**已在各大平台下架且无法找到帮助文档。  \n"
                    "但您仍可通过 QtAdb 激活它的设备管理员模式。  \n"
                    "**请退出所有帐号**，如小米帐号、华为帐号、Google 帐号等，激活后可以再重新登录。可前往QtAdb的[其它] -> [帐户]查看并删除账号。  \n"
                    "**请删除所有用户**，包括手机分身等，可前往QtAdb的[软件包管理器] -> [用户]中查看现有用户。  \n",
                    "adb shell dpm set-device-owner com.hld.apurikakusu/.receiver.DPMReceiver");
        return page;
        break;
    }
    case 8 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/taichi.png);", "激活 太极",
                    "**阴阳之门的用途**  \n"
                    "1. 可以大幅优化 太极 创建应用和升级应用的流程；不再需要手动确认，整个流程可以一气呵成。  \n"
                    "2. 额外提供类似冰箱的冻结功能；可以冻结和隐藏应用。  \n\n"
                    "**注意事项**  \n"
                    "1. 首先确保您已安装太极。  \n"
                    "2. **请退出所有帐号**，如小米帐号、华为帐号、Google 帐号等，激活后可以再重新登录。可前往QtAdb的[其它] -> [帐户]查看并删除账号。  \n"
                    "3. **请删除所有用户**，包括手机分身等，可前往QtAdb的[软件包管理器] -> [用户]中查看现有用户。  \n",
                    "adb shell dpm set-device-owner me.weishu.exp/.DeviceAdmin");
        return page;
        break;
    }
    case 9 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/island.png);", "激活 炼妖壶Island - 上帝模式",
                    "激活 Island 『上帝模式』：（可冻结任何应用，而不仅限于 Island 空间内的应用）  \n"
                    "1. **请退出所有帐号**，如小米帐号、华为帐号、Google 帐号等，激活后可以再重新登录。可前往QtAdb的[其它] -> [帐户]查看并删除账号。  \n"
                    "2. **请删除所有用户**，包括手机分身等，可前往QtAdb的[软件包管理器] -> [用户]中查看现有用户。  \n"
                    "3. 如果你已经创建了 Island 空间（Work profile），也必须先在 Island - Settings - Setup 中移除。在激活『上帝模式』后，你可以再重新创建 Island 空间。  \n",
                    "adb -d shell dpm set-device-owner com.oasisfeng.island/.IslandDeviceAdminReceiver");
        return page;
        break;
    }
    case 10 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/scene5.png);", "激活 Scene5",
                    "激活 Scene5 的 ADB 模式  \n"
                    "可以使用大部分查看功能和部分修改功能  \n",
                    "adb shell sh /sdcard/Android/data/com.omarea.vtools/up.sh");
        return page;
        break;
    }

    case 11 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/watchfps.png);", "激活 看帧数+",
                    "激活 看帧数+ 的 ADB 模式  \n"
                    "在屏幕上直观的显示当前帧数。  \n"
                    "方便、简单、美观。  \n"
                    "不用复杂的操作，没有任何风险  \n",
                    "adb shell sh /sdcard/Download/watchfps/watchfps.sh");
        return page;
        break;
    }

    case 12 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/permissiondog.png);", "激活 权限狗",
                    "激活 权限狗 的 ADB 模式  \n"
                    "**什么是 AppOps?**  \n"
                    "AppOps 是 Android 系统内存在的一个权限管理功能.与大家熟知的 运行时权限 不同,它至今没有开放管理入口,因此这项功能鲜为人知.  \n"
                    "正因为包括许多开发者的人们不了解 AppOps,应用通常不会检测 AppOps 设置,我们得以借助它在不会被应用发现的条件下拒绝应用申请的权限.(例如某应用不授权定位权限就无法使用,我们可以设置此应用的 AppOps 定位权限为忽略.这样我们就可以在拒绝定位权限后正常使用此应用了.)  \n"
                    "**权限狗又是什么?**  \n"
                    "我们知道,Android 尚未开放 AppOps 管理功能.而权限狗就是一个能够管理 AppOps 设置的第三方工具.  \n",
                    "adb shell sh /storage/emulated/0/Android/data/com.web1n.permissiondog/files/starter.sh");
        return page;
        break;
    }

    case 13 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/hail.png);", "激活 雹",
                    "激活 雹 的 「设备所有者 - 隐藏」 模式  \n"
                    "此模式通过将雹设置为设备所有者 (Device Owner)，调用```DevicePolicyManager.setApplicationHidden```方法隐藏应用。  \n"
                    "**请退出所有帐号**，如小米帐号、华为帐号、Google 帐号等，激活后可以再重新登录。可前往QtAdb的[其它] -> [帐户]查看并删除账号。  \n"
                    "**请删除所有用户**，包括手机分身等，可前往QtAdb的[软件包管理器] -> [用户]中查看现有用户。  \n",
                    "adb shell dpm set-device-owner com.aistra.hail/.receiver.DeviceAdminReceiver");
        return page;
        break;
    }

    case 14 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/bg.png);", "为 BatteryGuru 授予 使用情况访问 权限",
                    "授予 BatteryGuru 使用情况访问权限  \n"
                    "在某些定制 ROM 上可能不会生效  \n"
                    "授予应用程序权限，否则 BatteryGuru 的一些功能将无法工作。  \n",
                    "adb shell pm grant com.paget96.batteryguru android.permission.PACKAGE_USAGE_STATS");
        return page;
        break;
    }

    case 15 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/bg.png);", "为 BatteryGuru 授予 修改安全系统设置 权限",
                    "授予 BatteryGuru 修改安全系统设置权限  \n"
                    "在某些定制 ROM 上可能不会生效  \n"
                    "用于更改一些系统设置，例如 Android Doze 参数或系统节电状态  \n"
                    "也可以使用 Root  \n",
                    "adb shell pm grant com.paget96.batteryguru android.permission.WRITE_SECURE_SETTINGS");
        return page;
        break;
    }

    case 16 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/bg.png);", "为 BatteryGuru 授予 DUMP 权限",
                    "授予 BatteryGuru 读取 DUMP 权限  \n"
                    "在某些定制 ROM 上可能不会生效  \n"
                    "允许应用检查系统内部状态的权限，用来检测设置状态（例如空闲和 Doze 模式）。  \n"
                    "也可以使用 Root  \n",
                    "adb shell pm grant com.paget96.batteryguru android.permission.DUMP");
        return page;
        break;
    }

    case 17 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/apkinstaller.png);", "激活 安装狮",
                    "激活 安装狮 - DPM  \n"
                    "安装狮的主要功能是安装APK和卸载应用  \n"
                    "除了原生 Android 外的绝大部分定制系统由于系统的限制，无法将本应用设置为默认安装与卸载应用,而且发起安装时这些系统会直接让系统默认的软件包安装程序来处理，也没有很好的解决办法  \n"
                    "这种情况推荐用本应用内的 选择文件安装 功能或用一些支持选择打开方式的文件管理器等来发起安装  \n"
                    "安装前请关闭Google Play的安全扫描，请在开发者选项打开USB安装、关闭监控ADB安装应用等等以防止安装失败。  \n"
                    "**请退出所有帐号**，如小米帐号、华为帐号、Google 帐号等，激活后可以再重新登录。可前往QtAdb的[其它] -> [帐户]查看并删除账号。  \n"
                    "**请删除所有用户**，包括手机分身等，可前往QtAdb的[软件包管理器] -> [用户]中查看现有用户。  \n",
                    "adb shell dpm set-device-owner com.modosa.apkinstaller/.receiver.AdminReceiver");
        return page;
        break;
    }

    case 18 :
    {
        sp_activator *page = new sp_activator(parent);
        page->setDev(dev);
        page->setUp("border:0px;image:url(:/activatorApps/image/activatorApps/default.gif);", "激活 Dhizuku",
                    "激活 Dhizuku  \n"
                    "Dhizuku 可被用于共享设备所有者权限(DeviceOwner)。  \n"
                    "同一个系统只能存在一个应用被设置为设备所有者，授予后该应用不能卸载。  \n"
                    "**请退出所有帐号**，如小米帐号、华为帐号、Google 帐号等，激活后可以再重新登录。可前往QtAdb的[其它] -> [帐户]查看并删除账号。  \n"
                    "**请删除所有用户**，包括手机分身等，可前往QtAdb的[软件包管理器] -> [用户]中查看现有用户。  \n",
                    "adb shell dpm set-device-owner com.rosan.dhizuku/.server.DhizukuDAReceiver");
        return page;
        break;
    }


    break;
    }

    return NULL;
}

animationWidget* sonPageManager::createSonPageFor_apps(QWidget *parent, int key, device dev)
{
    switch(key +1)
    {
    case 1:
    {
        sp_installer *page = new sp_installer(parent);
        page->setDev(dev);
        return page;
    }
    case 2:
    {
        sp_permissionGroups *page = new sp_permissionGroups(parent);
        page->setDev(dev);
        return page;
    }
    case 3:
    {
        sp_permissions *page = new sp_permissions(parent);
        page->setDev(dev);
        return page;
    }
    case 4:
    {
        sp_packages *page = new sp_packages(parent);
        page->setDev(dev);
        return page;
    }
    case 5:
    {
        //qDebug() << "SPM.DEV = " << dev.model;
        sp_features *page = new sp_features(parent);
        page->setDev(dev);
        return page;
    }
    case 6:
    {
        sp_libraries *page = new sp_libraries(parent);
        page->setDev(dev);
        return page;
    }
    case 7:
    {
        sp_users *page = new sp_users(parent);
        page->setDev(dev);
        return page;
    }
        break;
    }
    return NULL;
}

animationWidget* sonPageManager::createSonPageFor_devControl(QWidget *parent, int key, device dev)
{
    switch(key +1)
    {
    case 1:
    {
        sp_devControl_power *page = new sp_devControl_power(parent);
        page->setDev(dev);
        return page;
    }
    case 2:
    {
        btnEmulator *page = new btnEmulator(parent);
        page->setDev(dev);
        return page;
    }
        break;
    }
    return NULL;
}

animationWidget* sonPageManager::createSonPageFor_recovery(QWidget *parent, int key, device dev)
{
    switch(key +1)
    {
    case 1:
    {
        sp_recovery *page = new sp_recovery(parent);
        page->setDev(dev);
        return page;
    }
        break;
    }
    return NULL;
}

animationWidget* sonPageManager::createSonPageFor_advanced(QWidget *parent, int key, device dev)
{
    switch(key +1)
    {
    case 1:
    {
        sp_customize_cmd *page = new sp_customize_cmd(parent);
        //page->setDev(dev);
        return page;
    }
    case 2:
    {
        sp_accounts *page = new sp_accounts(parent);
        page->setDev(dev);
        return page;
    }
    case 3:
    {
        sp_captive_portal *page = new sp_captive_portal(parent);
        page->setDev(dev);
        return page;
    }
    case 4:
    {
        sp_scales *page = new sp_scales(parent);
        page->setDev(dev);
        return page;
    }
    case 5:
    {
        sp_status_bar *page = new sp_status_bar(parent);
        page->setDev(dev);
        return page;
    }

    case 6:
    {
        sp_vibrate *page = new sp_vibrate(parent);
        page->setDev(dev);
        return page;
    }

        break;
    }
    return NULL;
}
