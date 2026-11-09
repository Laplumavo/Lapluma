#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

int main() {
    // ===== 修改这里：学号和姓名 =====
    std::string studentId   = "20240001";
    std::string studentName = "张三";
    // ================================

    // 1. 构造桌面路径（Windows）
    const char* userProfile = std::getenv("USERPROFILE");
    if (!userProfile) {
        std::cerr << "无法获取用户目录" << std::endl;
        return 1;
    }
    fs::path desktop = fs::path(userProfile) / "Desktop";
    fs::path folder  = desktop / (studentId + "+" + studentName);

    // 2. 创建文件夹
    if (!fs::exists(folder)) {
        fs::create_directories(folder);
    }

    fs::path filePath = folder / "体育运动.rtf";

    // 3. 正文内容（已把“运动”替换为“sport”）
    std::string title = "大学生与sport";  // 标题中也替换
    std::string body1 =
        "大学生受益于sport，与国家重视体育、大力发展体育教育密不可分。2020年"
        "中共中央办公厅、国务院办公厅印发《关于全面加强和改进新时代学校体育工作的意"
        "见》，强调学校体育是实现立德树人根本任务、提升学生综合素质的基础性工程，是加"
        "快推进教育现代化、建设教育强国和体育强国的重要工作。“建设体育强国”也写入"
        "“十四五”规划纲要。";
    std::string body2 =
        "近日，中国青年报社中青校媒面向全国1000名大学生发起问卷调查，结果显"
        "示，92.97%受访大学生认为sport是重要的，其中48.25%认为参与sport非常重"
        "要。81.02%受访者认为sport带来的收获是增强体质，66.18%期待通过sport控制体重，"
        "58.15%会通过sport休闲放松、缓解压力。";

    // 4. 打开文件写入 RTF
    std::ofstream out(filePath, std::ios::binary);
    if (!out) {
        std::cerr << "无法创建文件" << std::endl;
        return 1;
    }

    // RTF 文件头
    out << "{\\rtf1\\ansi\\deff0\n";
    out << "{\\fonttbl{\\f0\\fnil\\fcharset134 宋体;}{\\f1\\fnil\\fcharset134 楷体;}}\n";

    // ===== 标题段落 =====
    // 三号 = 16pt，楷体，加粗，居中，段后 16pt
    // \qc 居中，\b 加粗，\f1 楷体，\fs32 表示 16pt（半磅为单位，32=16*2）
    // \sb 段前，\sa 段后（单位：缇 twips，1pt=20缇，16pt=320缇）
    // \sl360\slmult1 表示 1.5 倍行距（240*1.5=360）
    // \li 左缩进，\ri 右缩进，\fi 首行缩进（1.2cm≈680缇，0.8cm≈454缇）
    out << "\\pard\\qc\\b\\f1\\fs32\\sa320\\sl360\\slmult1"
        << "\\li680\\ri680\\fi454 "
        << title << "\\par\n";

    // ===== 正文段落 =====
    // 小四 = 12pt（fs24），宋体（f0），段后 12pt（sa240），行距 1.5 倍
    auto writeBody = [&](const std::string& text) {
        out << "\\pard\\ql\\b0\\f0\\fs24\\sa240\\sl360\\slmult1"
            << "\\li680\\ri680\\fi454 "
            << text << "\\par\n";
    };
    writeBody(body1);
    writeBody(body2);

    // RTF 文件尾
    out << "}\n";
    out.close();

    std::cout << "生成成功：" << filePath.string() << std::endl;
    std::cout << "请用 Word 打开该 .rtf 文件，然后【另存为】->【Word 文档(*.docx)】" << std::endl;
    return 0;
}