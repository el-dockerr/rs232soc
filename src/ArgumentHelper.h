// ArgumentHelper.h
// Author: Swen Kalski <swen.kalski@camaleao-studio.com>

#pragma once


#ifndef ARGUMENT_HELPER_H
#define ARGUMENT_HELPER_H

void killProcessWithArgumentException(string e) {
    cout << e << endl;
    cout << "Please check arguments - abort!" << endl;
    exit(1);
}

bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}

void parseArguments(InputParser input) {
    if (input.cmdOptionExists("-p") && input.getCmdOption("-p").length() <= 5) {
        port = input.getCmdOption("-p");
    }
    else {
        killProcessWithArgumentException("No -p (serial device) given or to long");
    }

    const std::string& filename = input.getCmdOption("-tf");
    if (!filename.empty() && input.getCmdOption("-tf").length() <= 256 && fileExists(filename)) {
        truststoreFile = filename;
    }
    else {
        killProcessWithArgumentException("No or incorrect -tf (truststorefile) given or to long");
    }

    const std::string& truststpw = input.getCmdOption("-tp");
    if (!truststpw.empty() && input.getCmdOption("-tp").length() <= 256 && fileExists(truststpw)) {
        truststorePW = truststpw;
    }
    else {
        killProcessWithArgumentException("No or incorrect -tp (truststores password) given or to long");
    }

    const std::string& ksfilename = input.getCmdOption("-kf");
    if (!ksfilename.empty() && input.getCmdOption("-kf").length() <= 256 && fileExists(ksfilename)) {
        keystoreFile = ksfilename;
    }
    else {
        killProcessWithArgumentException("No or incorrect -kf (keystore file) given or to long");
    }

    const std::string& kspw = input.getCmdOption("-kp");
    if (!kspw.empty() && input.getCmdOption("-kp").length() <= 256 && fileExists(kspw)) {
        keystorePW = kspw;
    }
    else {
        killProcessWithArgumentException("No or incorrect -kf (keystore password) given or to long");
    }

    const std::string& k = input.getCmdOption("-k");
    if (!k.empty() && input.getCmdOption("-k").length() <= 256 && fileExists(k)) {
        keyPW = k;
    }
    else {
        killProcessWithArgumentException("No or incorrect -kf (keystore password) given or to long");
    }
}

#endif
