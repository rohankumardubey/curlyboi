# -*- coding: utf-8 -*-

VERSION = (0, 3, 0)
PRERELEASE = None  # alpha, beta or rc
REVISION = None


def generate_version(version, prerelease=None, revision=None):
    version_parts = [".".join(map(str, version))]
    if prerelease is not None:
        version_parts.append(f"-{prerelease}")
    if revision is not None:
        version_parts.append(f".{revision}")
    return "".join(version_parts)


__title__ = "curlyboi"
__description__ = "A simple curlyboi game written in C using ncurses."
__url__ = "https://github.com/vinayak-mehta/curlyboi"
__version__ = generate_version(VERSION, prerelease=PRERELEASE, revision=REVISION)
__maintainer__ = "Vinayak Mehta"
__maintainer_email__ = "vmehta94@gmail.com"
__license__ = "MIT"
