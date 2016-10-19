{
  "targets" : [
    {
      "target_name": "example",
      "sources" : [
        "datatypes.cpp"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}