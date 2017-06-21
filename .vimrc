let mapleader = ','
map <leader>l :set invnumber<cr>
filetype plugin indent on
syntax on
autocmd BufNewFile,BufReadPost *.tin,*.tac set filetype=cpp
highlight OverLength ctermbg=red ctermfg=white guibg=#592929
match OverLength /\%86v.*/
set tabstop=3 expandtab shiftwidth=3 softtabstop=3
map <leader>s :w!<cr>
map <leader>q :quit!<cr>
map <leader>w :wq!<cr>


function! GetTacTin()
python << EOF
import vim
name = vim.eval( 'bufname("%")' )
if name[ -4: ] == ".tac":
   toOpen = name[ :-4 ] + '.tin'
elif name[ -4: ] == ".tin":
   toOpen = name[ :-4 ] + '.tac'
            
comm = 'vs '+ toOpen
vim.command( comm )
EOF
endfunction
nnoremap <F1> :call GetTacTin()<CR>

function! PrintGrokUrl()
python << EOF
import vim
name = vim.eval('expand("<cword>")')
print "http://adflkjalkfdjalfskjasfl;kj/source/search?q=%s" % name
EOF
endfunction
map <F4> :call PrintGrokUrl()<CR>
