/*
 * This file is part of PCAPdroid.
 *
 * PCAPdroid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PCAPdroid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PCAPdroid.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2020-26 - Emanuele Faranda
 */

package com.emanuelef.remote_capture.activities;

import android.content.SharedPreferences;
import android.os.Bundle;

import androidx.appcompat.widget.SwitchCompat;
import androidx.preference.PreferenceManager;

import com.emanuelef.remote_capture.CaptureService;
import com.emanuelef.remote_capture.R;
import com.emanuelef.remote_capture.model.Prefs;

public class SimpleBlockActivity extends BaseActivity {
    private SharedPreferences mPrefs;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setTheme(R.style.AppTheme_NoActionBar);
        super.onCreate(savedInstanceState);
        setContentView(R.layout.simple_block_activity);
        setTitle(R.string.simple_block);
        setSupportActionBar(findViewById(R.id.toolbar));
        displayBackAction();

        mPrefs = PreferenceManager.getDefaultSharedPreferences(this);

        SwitchCompat port80 = findViewById(R.id.block_port80_switch);
        SwitchCompat alibaba = findViewById(R.id.block_alibaba_switch);

        port80.setChecked(Prefs.blockOutgoingPort80(mPrefs));
        alibaba.setChecked(Prefs.blockAlibabaDns(mPrefs));

        port80.setOnCheckedChangeListener((button, checked) -> {
            mPrefs.edit().putBoolean(Prefs.PREF_SIMPLE_BLOCK_PORT80, checked).apply();
            CaptureService.applySimpleBlocksFromPrefs();
        });
        alibaba.setOnCheckedChangeListener((button, checked) -> {
            mPrefs.edit().putBoolean(Prefs.PREF_SIMPLE_BLOCK_ALIBABA, checked).apply();
            CaptureService.applySimpleBlocksFromPrefs();
        });
    }
}
