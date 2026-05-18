-- bootstrap lazy.nvim
local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
  vim.fn.system({"git", "clone", "--filter=blob:none",
    "https://github.com/folke/lazy.nvim.git",
    "--branch=stable", lazypath})
end
vim.opt.rtp:prepend(lazypath)

-- opcoes basicas
vim.opt.number = true
vim.opt.relativenumber = true
vim.opt.tabstop = 2
vim.opt.shiftwidth = 2
vim.opt.expandtab = true
vim.opt.smartindent = true
vim.opt.wrap = false
vim.opt.termguicolors = true
vim.opt.signcolumn = "yes"
vim.opt.updatetime = 250
vim.opt.scrolloff = 8
vim.opt.hlsearch = false
vim.opt.incsearch = true
vim.g.mapleader = " "

-- plugins
require("lazy").setup({
  -- tema
  { "rose-pine/neovim", name = "rose-pine", priority = 1000,
    config = function()
      require("rose-pine").setup({ variant = "moon" })
      vim.cmd("colorscheme rose-pine")
    end },

  -- treesitter
  { "nvim-treesitter/nvim-treesitter", build = ":TSUpdate",
    config = function()
      require("nvim-treesitter").setup({
        ensure_installed = { "lua", "bash", "c", "nix", "python" },
        highlight = { enable = true },
      })
    end },

  -- telescope
  { "nvim-telescope/telescope.nvim", tag = "0.1.8",
    dependencies = { "nvim-lua/plenary.nvim" },
    config = function()
      local t = require("telescope.builtin")
      vim.keymap.set("n", "<leader>ff", t.find_files)
      vim.keymap.set("n", "<leader>fg", t.live_grep)
      vim.keymap.set("n", "<leader>fb", t.buffers)
    end },

  -- lsp + mason
  { "williamboman/mason.nvim", config = true },
  { "williamboman/mason-lspconfig.nvim",
    config = function()
      require("mason-lspconfig").setup({
        ensure_installed = { "lua_ls" },
        automatic_installation = true,
      })
    end },
  { "neovim/nvim-lspconfig",
    config = function()
      local lsp = require("lspconfig")
      lsp.lua_ls.setup({})
      lsp.bashls.setup({})
      lsp.nil_ls.setup({})
      vim.keymap.set("n", "gd", vim.lsp.buf.definition)
      vim.keymap.set("n", "K", vim.lsp.buf.hover)
      vim.keymap.set("n", "<leader>rn", vim.lsp.buf.rename)
      vim.keymap.set("n", "<leader>ca", vim.lsp.buf.code_action)
    end },

  -- autocomplete
  { "hrsh7th/nvim-cmp",
    dependencies = {
      "hrsh7th/cmp-nvim-lsp",
      "hrsh7th/cmp-buffer",
      "hrsh7th/cmp-path",
      "L3MON4D3/LuaSnip",
      "saadparwaiz1/cmp_luasnip",
    },
    config = function()
      local cmp = require("cmp")
      local luasnip = require("luasnip")
      cmp.setup({
        snippet = { expand = function(args) luasnip.lsp_expand(args.body) end },
        mapping = cmp.mapping.preset.insert({
          ["<C-Space>"] = cmp.mapping.complete(),
          ["<CR>"] = cmp.mapping.confirm({ select = true }),
          ["<Tab>"] = cmp.mapping(function(fallback)
            if cmp.visible() then cmp.select_next_item()
            else fallback() end
          end, {"i","s"}),
        }),
        sources = cmp.config.sources({
          { name = "nvim_lsp" }, { name = "luasnip" },
        }, { { name = "buffer" }, { name = "path" } }),
      })
    end },

  -- comentarios
  { "numToStr/Comment.nvim", config = true },

  -- status line
  { "nvim-lualine/lualine.nvim",
    config = function()
      require("lualine").setup({ options = { theme = "rose-pine" } })
    end },

  -- tela inicial
  { "goolord/alpha-nvim",
    dependencies = { "nvim-tree/nvim-web-devicons" },
    config = function()
      local alpha = require("alpha")
      local dashboard = require("alpha.themes.dashboard")

      -- cores do setup
      vim.api.nvim_set_hl(0, "AlphaHeader", { fg = "#b08090" })
      vim.api.nvim_set_hl(0, "AlphaButtons", { fg = "#f0e8ec" })
      vim.api.nvim_set_hl(0, "AlphaShortcut", { fg = "#2a1018", bg = "#b08090" })
      vim.api.nvim_set_hl(0, "AlphaFooter", { fg = "#4a3040" })

      dashboard.section.header.val = {
        "                                                      ",
        "  ░█████╗░██████╗░███████╗███████╗██╗  ██╗██████╗░  ",
        "  ██╔══██╗██╔══██╗██╔════╝██╔════╝██║░██╔╝██╔══██╗  ",
        "  ██║░░██║██████╦╝█████╗░░███████╗█████═╝░██████╦╝  ",
        "  ██║░░██║██╔══██╗██╔══╝░░╚════██║██╔═██╗░██╔══██╗  ",
        "  ╚█████╔╝██████╦╝███████╗███████║██║░╚██╗██████╦╝  ",
        "  ░╚════╝░╚═════╝░╚══════╝╚══════╝╚═╝░░╚═╝╚═════╝░  ",
        "                                                      ",
      }
      dashboard.section.header.opts.hl = "AlphaHeader"

      dashboard.section.buttons.val = {
        dashboard.button("f", "  buscar arquivo",  ":Telescope find_files<CR>"),
        dashboard.button("r", "  recentes",        ":Telescope oldfiles<CR>"),
        dashboard.button("g", "  grep",            ":Telescope live_grep<CR>"),
        dashboard.button("e", "  novo arquivo",    ":ene <BAR> startinsert<CR>"),
        dashboard.button("q", "  sair",            ":qa<CR>"),
      }
      for _, btn in ipairs(dashboard.section.buttons.val) do
        btn.opts.hl = "AlphaButtons"
        btn.opts.hl_shortcut = "AlphaShortcut"
      end

      dashboard.section.footer.val = "nixos + dwl + rose-pine"
      dashboard.section.footer.opts.hl = "AlphaFooter"

      alpha.setup(dashboard.opts)
    end },
})
