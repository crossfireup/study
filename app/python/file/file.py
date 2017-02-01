#/usr/bin/env python
# -*- coding:gbk -*-

import os
import sys
import fnmatch
import traceback
import codecs
import shutil


def match_file(dirpath):
    dirpath = os.path.normpath(os.path.join("\\\\?\\" + dirpath + "\\"))
    if not os.path.isdir(dirpath):
        print >>sys.stderr, "not a valid directory"
        return
    else:
        # print(dirpath)
        os.listdir(dirpath)
        f_keep = codecs.open('video.log', 'w', encoding='gbk')
        f_del = codecs.open('del.log', 'w', encoding='gbk')
        for curdir, dirnames, files in os.walk(dirpath, topdown=True):
            # print files
            # dir1 = curdir + dirnames[0] + '\\'
            # print dir1,'      ', dirnames[0]
            # print os.listdir(dir1)
            if not os.listdir(curdir):
                os.rmdir(curdir)
            for filename in files:
                # print unicode(filename)
                # print filename
                full_name = os.path.join(curdir, filename)
                file_stat = os.stat(full_name)
                try:
                    if file_stat.st_size > 1014 * 1024 * 20:
                        # print type(full_name)
                        # print curdir.encode('unicode_escape').decode('unicode_escape')
                        # print type(filename)
                        # print filename.encode('unicode_escape').decode('unicode_escape')
                        # print full_name
                        print full_name
                        f_keep.write(full_name + '\n')
                    else:
                        _file, file_ext = os.path.splitext(full_name)
                        print file_ext
                        if file_ext == u'.log':
                            continue
                        f_del.write(full_name + '\n')
                        new_dir = os.path.join(dirpath, 'delete')
                        new_name = os.path.join(new_dir, filename)
                        if not os.path.exists(os.path.dirname(new_dir)):
                            os.mkdir(new_dir)
                        f_del.write(new_name + '\n')
                        shutil.move(full_name, new_name)
                        # os.rename(full_name, new_name)
                except:
                    exc_type, exc_value, exc_traceback = sys.exc_info()
                    traceback.print_exception(
                        exc_type, exc_value, exc_traceback, file=sys.stderr)
                    pass
        f_keep.flush()
        f_keep.close()
        f_del.flush()
        f_del.close()

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print >> sys.stderr, "%s dirname" % (sys.argv[0])
        exit(1)
    try:
        match_file(sys.argv[1])
    except:
        exc_type, exc_value, exc_traceback = sys.exc_info()
        traceback.print_exception(
            exc_type, exc_value, exc_traceback, file=sys.stderr)
        os._exit(1)
