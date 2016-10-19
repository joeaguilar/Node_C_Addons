{
  "targets" : [
    {
      "target_name": "addon",
      "sources": ["complex.cpp"],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
