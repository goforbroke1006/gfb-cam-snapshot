#include <iostream>

#include <opencv/cv.h>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>

#include <boost/filesystem/operations.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace cv;

namespace fs = boost::filesystem;
namespace pt = boost::posix_time;

std::string
FormatTime(pt::ptime now) {
    std::ostringstream is;
    static std::locale loc(is.getloc(), new pt::time_facet("%Y-%m-%d-%H-%M-%S"));

    is.imbue(loc);
    is << now;
    return is.str();
}

fs::path
expand(fs::path in) {
    if (in.empty()) return in;

    const char *home = getenv("HOME");
    if (home == nullptr) {
        std::cerr << "error: HOME variable not set." << std::endl;
        throw std::invalid_argument("error: HOME environment variable not set.");
    }

    std::string s = in.c_str();
    if (s[0] == '~') {
        s = std::string(home) + s.substr(1, s.size() - 1);
        return fs::path(s);
    } else {
        return in;
    }
}

int main() {

    const fs::path &targetDir = expand(fs::path("~/gfb-cam-snapshot"));
    if (!fs::exists(targetDir)) {
        if (!fs::create_directories(targetDir)) {
            std::cerr << "ERROR! Unable to create target dir : " << targetDir << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    cv::VideoCapture cap;
    cap.open(0);

    int deviceID = 0;
    int apiID = cv::CAP_ANY;

    cap.open(deviceID + apiID);
    if (!cap.isOpened()) {
        std::cerr << "ERROR! Unable to open camera" << std::endl;
        exit(EXIT_FAILURE);
    }

    Mat frame;
    cap.read(frame);

    if (frame.empty()) {
        std::cerr << "ERROR! blank frame" << std::endl;
        exit(EXIT_FAILURE);
    }

    pt::ptime now = boost::posix_time::second_clock::local_time();

    char filename[256];
    sprintf(filename, "%s/snapshot-%s.jpg", targetDir.c_str(), FormatTime(now).c_str());

    if (cv::imwrite(filename, frame))
        std::cout << "write to " << filename << std::endl;

    return 0;

}