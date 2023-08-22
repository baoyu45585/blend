package com.example.blend;

import android.content.Intent;
import android.os.Bundle;


import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private RecyclerView recyclerView;
    List<MyBean> list = new ArrayList<>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        String[] names = {"左右开幕式", "左右闭幕式", "上下闭幕式", "上下开幕式"};
        String[] paths = {"lr_open","lr_close","up_down_close","up_down_open"};
        if (names.length == paths.length) {
            for (int i = 0; i < names.length; i++) {
                MyBean nameBean = new MyBean();
                nameBean.setName(names[i]);
                nameBean.setPath(paths[i]);
                list.add(nameBean);
            }
        }
        recyclerView = (RecyclerView) findViewById(R.id.recyclerView);
        recyclerView.setLayoutManager(new LinearLayoutManager(this));
        MyAdapter myAdapter = new MyAdapter(this, list);
        myAdapter.setOnItemClickListener(new MyAdapter.OnItemClickListener() {
            @Override
            public void onItemClick(View view, int position) {
                Toast.makeText(MainActivity.this, list.get(position).getName(), Toast.LENGTH_SHORT).show();
                Intent intent=new Intent(MainActivity.this,TextureActivity.class);
                intent.putExtra("path",list.get(position).getPath());
                startActivity(intent);
            }
        });
        recyclerView.setAdapter(myAdapter);
    }
}
