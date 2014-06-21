#pragma once

#include <base/thread_pool.h>

namespace dist_clang {
namespace daemon {

class FileCache {
 public:
  enum : ui64 {
    UNLIMITED = 0,
  };

  struct Entry {
    String object_path;
    String deps_path;
    String stderr;
  };

  using Optional = base::ThreadPool::Optional;

  explicit FileCache(const String& path);
  FileCache(const String& path, ui64 size);

  String Hash(const String& code, const String& command_line,
              const String& version) const;
  bool Find(const String& code, const String& command_line,
            const String& version, Entry* entry) const;
  Optional Store(const String& code, const String& command_line,
                 const String& version, const Entry& entry);
  void StoreNow(const String& code, const String& command_line,
                const String& version, const Entry& entry);

 private:
  const String path_;
  base::ThreadPool pool_;
  ui64 max_size_, cached_size_;

  void DoStore(const String& hash, const Entry& entry);
};

}  // namespace daemon
}  // namespace dist_clang
